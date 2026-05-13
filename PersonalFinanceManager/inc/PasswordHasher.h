#ifndef INC_PASSWORD_HASHER_H
#define INC_PASSWORD_HASHER_H

#include <string>

namespace finance
{
class PasswordHasher
{
   public:
    static std::string hashPassword(const std::string& password);
    static bool verifyPassword(const std::string& password, const std::string& hash);

   private:
    static std::string toHex(const unsigned char* bytes, size_t length);
};

}  // namespace finance

#endif  // INC_PASSWORD_HASHER_H
