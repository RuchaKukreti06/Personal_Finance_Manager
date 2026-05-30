#ifndef FINANCE_SERVER_MIDDLEWARE_AUTHMIDDLEWARE_H
#define FINANCE_SERVER_MIDDLEWARE_AUTHMIDDLEWARE_H

#include "auth/JwtManager.h"
#include <httplib.h>
#include <optional>

namespace middleware {

class AuthMiddleware {
public:
    static std::optional<auth::TokenPayload> authenticate(const httplib::Request& request);
    static void handleUnauthorized(httplib::Response& response);
};

}

#endif
