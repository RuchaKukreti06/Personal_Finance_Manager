#include "../inc/PasswordHasher.h"

#include <openssl/sha.h>

#include <iomanip>
#include <sstream>

namespace finance
{
std::string PasswordHasher::toHex(const unsigned char* bytes, size_t length)
{
    std::ostringstream stream;
    stream << std::hex << std::setfill('0');

    for (size_t i = 0; i < length; ++i)
    {
        stream << std::setw(2) << static_cast<int>(bytes[i]);
    }

    return stream.str();
}

std::string PasswordHasher::hashPassword(const std::string& password)
{
    unsigned char digest[SHA256_DIGEST_LENGTH] = {0};
    SHA256(reinterpret_cast<const unsigned char*>(password.data()), password.size(), digest);

    return toHex(digest, SHA256_DIGEST_LENGTH);
}

bool PasswordHasher::verifyPassword(const std::string& password, const std::string& hash)
{
    return hashPassword(password) == hash;
}

}  // namespace finance
