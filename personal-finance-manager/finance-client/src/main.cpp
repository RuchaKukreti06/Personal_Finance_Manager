#include "api/ApiClient.h"
#include "api/AuthSession.h"
#include "screens/LoginScreen.h"
#include "screens/RegisterScreen.h"
#include "screens/DashboardScreen.h"
#include <iostream>
#include <string>

int main() {
    api::ApiClient client("http://localhost:8080");

    std::cout << "=== Personal Finance Manager ===\n";

    while (true) {
        if (api::AuthSession::instance().isLoggedIn()) {
            screens::showDashboardScreen(client);
            continue;
        }

        std::cout << "\n1. Login\n";
        std::cout << "2. Register\n";
        std::cout << "3. Exit\n";
        std::cout << "Choice: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            screens::showLoginScreen(client);
        } else if (choice == "2") {
            screens::showRegisterScreen(client);
        } else if (choice == "3") {
            std::cout << "Goodbye!\n";
            return 0;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}