#include "screens/LoginScreen.h"
#include "api/AuthSession.h"
#include <iostream>
#include <string>

namespace screens {

void showLoginScreen(api::ApiClient& client) {
    std::string username;
    std::string password;

    std::cout << "\n===== LOGIN =====\n";
    std::cout << "Username: ";
    std::getline(std::cin, username);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    auto result = client.post("/api/auth/login", {{"username", username}, {"password", password}});

    if (result["success"].get<bool>()) {
        std::string token = result["token"].get<std::string>();
        api::AuthSession::instance().login(token, username);
        client.setToken(token);
        std::cout << "Login successful! Welcome, " << username << ".\n";
    } else {
        std::cout << "Error: " << result["error"].get<std::string>() << "\n";
    }
}

}