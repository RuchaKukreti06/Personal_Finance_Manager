#include <iostream>
#include <string>

#include "api/ApiClient.h"
#include "api/AuthSession.h"
#include "screens/DashboardScreen.h"
#include "screens/LoginScreen.h"
#include "screens/RegisterScreen.h"

int main()
{
    api::ApiClient client("http://127.0.0.1:8080");

    std::cout << "=== Personal Finance Manager ===\n";

    while (true)
    {
        if (api::AuthSession::instance().isLoggedIn())
        {
            screens::showDashboardScreen(client);
            continue;
        }

        std::cout << "\n1. Login\n";
        std::cout << "2. Register\n";
        std::cout << "3. Exit\n";
        std::cout << "Choice: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1")
        {
            screens::showLoginScreen(client);
        }
        else if (choice == "2")
        {
            screens::showRegisterScreen(client);
        }
        else if (choice == "3")
        {
            std::cout << "Goodbye!\n";
            return 0;
        }
        else
        {
            std::cout << "Invalid choice.\n";
        }
    }
}