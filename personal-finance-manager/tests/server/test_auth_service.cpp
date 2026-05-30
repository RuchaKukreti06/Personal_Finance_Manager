#include "auth/PasswordHasher.h"
#include "auth/JwtManager.h"
#include <iostream>
#include <cassert>
#include <string>

int passed = 0;
int failed = 0;

void check(bool condition, const std::string& name) {
    if (condition) {
        std::cout << "  [PASS] " << name << "\n";
        passed++;
    } else {
        std::cout << "  [FAIL] " << name << "\n";
        failed++;
    }
}

void testPasswordHasher() {
    std::cout << "\n--- PasswordHasher Tests ---\n";

    std::string hash = auth::PasswordHasher::hash("mypassword");
    check(!hash.empty(), "hash produces non-empty output");
    check(hash.find(':') != std::string::npos, "hash contains salt separator");

    check(auth::PasswordHasher::verify("mypassword", hash), "verify correct password returns true");
    check(!auth::PasswordHasher::verify("wrongpassword", hash), "verify wrong password returns false");
    check(!auth::PasswordHasher::verify("", hash), "verify empty password returns false");

    std::string hash2 = auth::PasswordHasher::hash("mypassword");
    check(hash != hash2, "two hashes of same password differ (unique salts)");

    check(auth::PasswordHasher::verify("mypassword", hash2), "verify works with second hash too");

    check(!auth::PasswordHasher::verify("mypassword", "invalid_no_colon"), "verify rejects malformed hash");
    check(!auth::PasswordHasher::verify("mypassword", ""), "verify rejects empty hash");
}

void testJwtManager() {
    std::cout << "\n--- JwtManager Tests ---\n";

    auth::JwtManager::instance().configure("test-secret-key-12345", 60);

    std::string token = auth::JwtManager::instance().generate(42, "john_doe");
    check(!token.empty(), "generate produces non-empty token");

    auto payload = auth::JwtManager::instance().validate(token);
    check(payload.has_value(), "validate returns payload for valid token");
    check(payload->userId == 42, "payload userId is correct");
    check(payload->username == "john_doe", "payload username is correct");

    auto bad1 = auth::JwtManager::instance().validate("garbage.token.here");
    check(!bad1.has_value(), "validate rejects garbage token");

    auto bad2 = auth::JwtManager::instance().validate("");
    check(!bad2.has_value(), "validate rejects empty token");

    std::string token2 = auth::JwtManager::instance().generate(99, "jane");
    auto payload2 = auth::JwtManager::instance().validate(token2);
    check(payload2.has_value() && payload2->userId == 99, "second token has correct userId");
    check(payload2.has_value() && payload2->username == "jane", "second token has correct username");

    auth::JwtManager::instance().configure("different-secret", 60);
    auto bad3 = auth::JwtManager::instance().validate(token);
    check(!bad3.has_value(), "token signed with old secret is rejected after secret change");

    auth::JwtManager::instance().configure("test-secret-key-12345", 0);
    std::string expiredToken = auth::JwtManager::instance().generate(1, "expired_user");
    auto bad4 = auth::JwtManager::instance().validate(expiredToken);
    check(!bad4.has_value(), "token with 0-minute expiration is rejected immediately");
}

int main() {
    std::cout << "=== Auth Unit Tests ===\n";

    testPasswordHasher();
    testJwtManager();

    std::cout << "\n=== Results: " << passed << " passed, " << failed << " failed ===\n";
    return failed > 0 ? 1 : 0;
}