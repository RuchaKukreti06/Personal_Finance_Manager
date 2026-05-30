#include "auth/PasswordHasher.h"

#include <openssl/rand.h>
#include <openssl/sha.h>

#include <iomanip>
#include <sstream>

namespace auth
{

std::string PasswordHasher::generateSalt()
{
    unsigned char bytes[16];
    RAND_bytes(bytes, sizeof(bytes));
    std::ostringstream oss;
    for (auto b : bytes)
    {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(b);
    }
    return oss.str();
}

std::string PasswordHasher::sha256(const std::string& input)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);
    std::ostringstream oss;
    for (auto b : hash)
    {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(b);
    }
    return oss.str();
}

std::string PasswordHasher::hash(const std::string& password)
{
    std::string salt = generateSalt();
    std::string hashed = sha256(salt + password);
    return salt + ":" + hashed;
}

bool PasswordHasher::verify(const std::string& password, const std::string& storedHash)
{
    auto pos = storedHash.find(':');
    if (pos == std::string::npos) return false;

    std::string salt = storedHash.substr(0, pos);
    std::string expected = storedHash.substr(pos + 1);
    std::string computed = sha256(salt + password);
    return computed == expected;
}

}
