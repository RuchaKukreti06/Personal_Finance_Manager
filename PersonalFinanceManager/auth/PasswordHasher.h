#pragma once

#include <string>

namespace finance
{
class PasswordHasher
{
   public:
    static std::string hashPassword(std::string const& password);
    static bool verifyPassword(std::string const& password, std::string const& hash);
};
}  // namespace finance
