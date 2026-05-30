#include "screens/RegisterScreen.h"
#include <iostream>
#include <string>

namespace screens {

void showRegisterScreen(api::ApiClient& client) {
    std::string username;
    std::string email;
    std::string password;

    std::cout << "\n===== REGISTER =====\n";
    std::cout << "Username: ";
    std::getline(std::cin, username);
    std::cout << "Email: ";
    std::getline(std::cin, email);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    auto result = client.post("/api/auth/register",
        {{"username", username}, {"email", email}, {"password", password}});

    if (result["success"].get<bool>()) {
        std::cout << "Registration successful! You can now login.\n";
    } else {
        std::cout << "Error: " << result["error"].get<std::string>() << "\n";
    }
}

}