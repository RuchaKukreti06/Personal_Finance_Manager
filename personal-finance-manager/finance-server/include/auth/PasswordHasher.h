#ifndef FINANCE_SERVER_AUTH_PASSWORDHASHER_H
#define FINANCE_SERVER_AUTH_PASSWORDHASHER_H

#include <string>

namespace auth {

class PasswordHasher {
public:
    static std::string hash(const std::string& password);
    static bool verify(const std::string& password, const std::string& storedHash);
};

}

#endif
