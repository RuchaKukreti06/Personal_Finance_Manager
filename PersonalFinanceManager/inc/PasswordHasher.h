#ifndef INC_PASSWORD_HASHER_H
#define INC_PASSWORD_HASHER_H

#include <string>

namespace finance
{
// Provides password hashing and verification using SHA256
class PasswordHasher
{
public:
    // Hash a plaintext password using SHA256
    static std::string hashPassword(const std::string& password);

    // Verify plaintext password against stored hash
    static bool verifyPassword(const std::string& password, const std::string& hash);

private:
    // Convert bytes to hexadecimal string representation
    static std::string toHex(const unsigned char* bytes, size_t length);
};

} // namespace finance

#endif // INC_PASSWORD_HASHER_H
