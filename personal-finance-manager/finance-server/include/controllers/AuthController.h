#ifndef FINANCE_SERVER_CONTROLLERS_AUTHCONTROLLER_H
#define FINANCE_SERVER_CONTROLLERS_AUTHCONTROLLER_H

#include <httplib.h>

namespace controllers {

class AuthController {
public:
    static void registerRoutes(httplib::Server& server);

private:
    static void handleRegister(const httplib::Request& request, httplib::Response& response);
    static void handleLogin(const httplib::Request& request, httplib::Response& response);
    static void handleChangePassword(const httplib::Request& request, httplib::Response& response);
};

}

#endif
