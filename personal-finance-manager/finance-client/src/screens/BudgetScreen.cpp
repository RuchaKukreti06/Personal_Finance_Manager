#include "screens/BudgetScreen.h"
#include <iostream>
#include <string>

namespace screens {

static void listBudgets(api::ApiClient& client) {
    auto result = client.get("/api/budgets");
    if (!result["success"].get<bool>()) {
        std::cout << "Error: " << result["error"].get<std::string>() << "\n";
        return;
    }
    auto budgets = result["budgets"];
    if (budgets.empty()) {
        std::cout << "No budgets found.\n";
        return;
    }
    std::cout << "\n--- Budgets ---\n";
    for (const auto& budget : budgets) {
        std::cout << "[" << budget["id"] << "] "
                  << budget["category"].get<std::string>() << " | Limit: $"
                  << budget["monthlyLimit"] << " | "
                  << budget["month"] << "/" << budget["year"] << "\n";
    }
}

static void addBudget(api::ApiClient& client) {
    std::string category, limit, month, year;

    std::cout << "Category: ";
    std::getline(std::cin, category);
    std::cout << "Monthly Limit: ";
    std::getline(std::cin, limit);
    std::cout << "Month (1-12): ";
    std::getline(std::cin, month);
    std::cout << "Year: ";
    std::getline(std::cin, year);

    auto result = client.post("/api/budgets", {
        {"category", category},
        {"monthlyLimit", std::stod(limit)},
        {"month", std::stoi(month)},
        {"year", std::stoi(year)}
    });

    if (result["success"].get<bool>()) {
        std::cout << "Budget created.\n";
    } else {
        std::cout << "Error: " << result["error"].get<std::string>() << "\n";
    }
}

static void checkAlerts(api::ApiClient& client) {
    std::string month, year;
    std::cout << "Month (1-12): ";
    std::getline(std::cin, month);
    std::cout << "Year: ";
    std::getline(std::cin, year);

    auto result = client.get("/api/budgets/alerts?month=" + month + "&year=" + year);
    if (!result["success"].get<bool>()) {
        std::cout << "Error: " << result["error"].get<std::string>() << "\n";
        return;
    }
    auto alerts = result["alerts"];
    if (alerts.empty()) {
        std::cout << "No budget alerts.\n";
        return;
    }
    std::cout << "\n--- Budget Alerts ---\n";
    for (const auto& alert : alerts) {
        std::cout << alert["category"].get<std::string>() << " | Spent: $"
                  << alert["spent"] << " / $" << alert["limit"]
                  << " (" << alert["percentage"] << "%) ["
                  << alert["level"].get<std::string>() << "]\n";
    }
}

static void deleteBudget(api::ApiClient& client) {
    std::string budgetId;
    std::cout << "Budget ID to delete: ";
    std::getline(std::cin, budgetId);

    auto result = client.del("/api/budgets/" + budgetId);
    if (result["success"].get<bool>()) {
        std::cout << "Budget deleted.\n";
    } else {
        std::cout << "Error: " << result["error"].get<std::string>() << "\n";
    }
}

void showBudgetScreen(api::ApiClient& client) {
    while (true) {
        std::cout << "\n===== BUDGETS =====\n";
        std::cout << "1. List budgets\n";
        std::cout << "2. Add budget\n";
        std::cout << "3. Check alerts\n";
        std::cout << "4. Delete budget\n";
        std::cout << "5. Back\n";
        std::cout << "Choice: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            listBudgets(client);
        } else if (choice == "2") {
            addBudget(client);
        } else if (choice == "3") {
            checkAlerts(client);
        } else if (choice == "4") {
            deleteBudget(client);
        } else if (choice == "5") {
            return;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

}