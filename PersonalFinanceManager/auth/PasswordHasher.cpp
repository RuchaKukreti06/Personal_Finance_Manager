#include "PasswordHasher.h"

#include <openssl/sha.h>

#include <iomanip>
#include <sstream>

namespace finance
{
namespace
{
std::string toHex(unsigned char const* bytes, size_t length)
{
    std::ostringstream stream;
    stream << std::hex << std::setfill('0');
    for (size_t index = 0; index < length; ++index)
    {
        stream << std::setw(2) << static_cast<int>(bytes[index]);
    }
    return stream.str();
}
}  // namespace

std::string PasswordHasher::hashPassword(std::string const& password)
{
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<unsigned char const*>(password.data()), password.size(), digest);
    return toHex(digest, SHA256_DIGEST_LENGTH);
}

bool PasswordHasher::verifyPassword(std::string const& password, std::string const& hash)
{
    return hashPassword(password) == hash;
}
}  // namespace finance
