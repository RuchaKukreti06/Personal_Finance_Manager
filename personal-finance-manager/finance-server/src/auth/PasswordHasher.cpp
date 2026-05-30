#include "auth/PasswordHasher.h"

#include <openssl/rand.h>
#include <openssl/sha.h>

#include <iomanip>
#include <sstream>

namespace auth
{

static std::string toHex(const unsigned char* data, size_t length)
{
    std::ostringstream stream;
    for (size_t index = 0; index < length; ++index)
    {
        stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[index]);
    }
    return stream.str();
}

static std::string sha256(const std::string& input)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);
    return toHex(hash, SHA256_DIGEST_LENGTH);
}

std::string PasswordHasher::hash(const std::string& password)
{
    unsigned char saltBytes[16];
    RAND_bytes(saltBytes, sizeof(saltBytes));
    std::string salt = toHex(saltBytes, sizeof(saltBytes));
    std::string hashed = sha256(salt + password);
    return salt + ":" + hashed;
}

bool PasswordHasher::verify(const std::string& password, const std::string& storedHash)
{
    if (password.empty() || storedHash.empty()) return false;

    size_t separatorPos = storedHash.find(':');
    if (separatorPos == std::string::npos) return false;

    std::string salt = storedHash.substr(0, separatorPos);
    std::string expectedHash = storedHash.substr(separatorPos + 1);
    std::string computedHash = sha256(salt + password);

    return computedHash == expectedHash;
}

}  // namespace auth
