#include "screens/DashboardScreen.h"
#include "screens/ExpenseScreen.h"
#include "screens/IncomeScreen.h"
#include "screens/BudgetScreen.h"
#include "screens/SummaryScreen.h"
#include "api/AuthSession.h"
#include <iostream>
#include <string>

namespace screens {

void showDashboardScreen(api::ApiClient& client) {
    while (true) {
        std::cout << "\n===== DASHBOARD (" << api::AuthSession::instance().username() << ") =====\n";
        std::cout << "1. Expenses\n";
        std::cout << "2. Incomes\n";
        std::cout << "3. Budgets\n";
        std::cout << "4. Monthly Summary\n";
        std::cout << "5. Logout\n";
        std::cout << "Choice: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            showExpenseScreen(client);
        } else if (choice == "2") {
            showIncomeScreen(client);
        } else if (choice == "3") {
            showBudgetScreen(client);
        } else if (choice == "4") {
            showSummaryScreen(client);
        } else if (choice == "5") {
            api::AuthSession::instance().logout();
            client.clearToken();
            std::cout << "Logged out.\n";
            return;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

}