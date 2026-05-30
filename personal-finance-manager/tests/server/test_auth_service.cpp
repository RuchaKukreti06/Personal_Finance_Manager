#include "auth/PasswordHasher.h"
#include "auth/JwtManager.h"
#include <gtest/gtest.h>
#include <string>

TEST(PasswordHasherTest, HashProducesNonEmptyOutput) {
    std::string hash = auth::PasswordHasher::hash("mypassword");
    EXPECT_FALSE(hash.empty());
}

TEST(PasswordHasherTest, HashContainsSaltSeparator) {
    std::string hash = auth::PasswordHasher::hash("mypassword");
    EXPECT_NE(hash.find(':'), std::string::npos);
}

TEST(PasswordHasherTest, VerifyCorrectPassword) {
    std::string hash = auth::PasswordHasher::hash("mypassword");
    EXPECT_TRUE(auth::PasswordHasher::verify("mypassword", hash));
}

TEST(PasswordHasherTest, VerifyWrongPassword) {
    std::string hash = auth::PasswordHasher::hash("mypassword");
    EXPECT_FALSE(auth::PasswordHasher::verify("wrongpassword", hash));
}

TEST(PasswordHasherTest, VerifyEmptyPassword) {
    std::string hash = auth::PasswordHasher::hash("mypassword");
    EXPECT_FALSE(auth::PasswordHasher::verify("", hash));
}

TEST(PasswordHasherTest, UniqueSaltsProduceDifferentHashes) {
    std::string hash1 = auth::PasswordHasher::hash("mypassword");
    std::string hash2 = auth::PasswordHasher::hash("mypassword");
    EXPECT_NE(hash1, hash2);
    EXPECT_TRUE(auth::PasswordHasher::verify("mypassword", hash1));
    EXPECT_TRUE(auth::PasswordHasher::verify("mypassword", hash2));
}

TEST(PasswordHasherTest, RejectsMalformedHash) {
    EXPECT_FALSE(auth::PasswordHasher::verify("mypassword", "invalid_no_colon"));
    EXPECT_FALSE(auth::PasswordHasher::verify("mypassword", ""));
}

class JwtManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        auth::JwtManager::instance().configure("test-secret-key-12345", 60);
    }
};

TEST_F(JwtManagerTest, GenerateProducesNonEmptyToken) {
    std::string token = auth::JwtManager::instance().generate(42, "john_doe");
    EXPECT_FALSE(token.empty());
}

TEST_F(JwtManagerTest, ValidateReturnsCorrectPayload) {
    std::string token = auth::JwtManager::instance().generate(42, "john_doe");
    auto payload = auth::JwtManager::instance().validate(token);
    ASSERT_TRUE(payload.has_value());
    EXPECT_EQ(payload->userId, 42);
    EXPECT_EQ(payload->username, "john_doe");
}

TEST_F(JwtManagerTest, RejectsGarbageToken) {
    auto result = auth::JwtManager::instance().validate("garbage.token.here");
    EXPECT_FALSE(result.has_value());
}

TEST_F(JwtManagerTest, RejectsEmptyToken) {
    auto result = auth::JwtManager::instance().validate("");
    EXPECT_FALSE(result.has_value());
}

TEST_F(JwtManagerTest, MultipleTokensValidateIndependently) {
    std::string token1 = auth::JwtManager::instance().generate(42, "john_doe");
    std::string token2 = auth::JwtManager::instance().generate(99, "jane");

    auto p1 = auth::JwtManager::instance().validate(token1);
    auto p2 = auth::JwtManager::instance().validate(token2);

    ASSERT_TRUE(p1.has_value());
    EXPECT_EQ(p1->userId, 42);
    ASSERT_TRUE(p2.has_value());
    EXPECT_EQ(p2->userId, 99);
    EXPECT_EQ(p2->username, "jane");
}

TEST_F(JwtManagerTest, RejectsTokenAfterSecretChange) {
    std::string token = auth::JwtManager::instance().generate(42, "john_doe");
    auth::JwtManager::instance().configure("different-secret", 60);
    auto result = auth::JwtManager::instance().validate(token);
    EXPECT_FALSE(result.has_value());
}

TEST_F(JwtManagerTest, RejectsExpiredToken) {
    auth::JwtManager::instance().configure("test-secret-key-12345", 0);
    std::string token = auth::JwtManager::instance().generate(1, "expired_user");
    auto result = auth::JwtManager::instance().validate(token);
    EXPECT_FALSE(result.has_value());
}

