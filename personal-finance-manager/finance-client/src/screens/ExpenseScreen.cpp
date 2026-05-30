#include "screens/ExpenseScreen.h"
#include <iostream>
#include <string>

namespace screens {

static void listExpenses(api::ApiClient& client) {
    auto result = client.get("/api/expenses");
    if (!result["success"].get<bool>()) {
        std::cout << "Error: " << result["error"].get<std::string>() << "\n";
        return;
    }
    auto expenses = result["expenses"];
    if (expenses.empty()) {
        std::cout << "No expenses found.\n";
        return;
    }
    std::cout << "\n--- Expenses ---\n";
    for (const auto& expense : expenses) {
        std::cout << "[" << expense["id"] << "] "
                  << expense["date"].get<std::string>() << " | "
                  << expense["category"].get<std::string>() << " | $"
                  << expense["amount"] << " | "
                  << expense["description"].get<std::string>() << "\n";
    }
}

static void addExpense(api::ApiClient& client) {
    std::string amount, category, description, date;

    std::cout << "Amount: ";
    std::getline(std::cin, amount);
    std::cout << "Category: ";
    std::getline(std::cin, category);
    std::cout << "Description: ";
    std::getline(std::cin, description);
    std::cout << "Date (YYYY-MM-DD): ";
    std::getline(std::cin, date);

    auto result = client.post("/api/expenses", {
        {"amount", std::stod(amount)},
        {"category", category},
        {"description", description},
        {"date", date}
    });

    if (result["success"].get<bool>()) {
        std::cout << "Expense added.\n";
    } else {
        std::cout << "Error: " << result["error"].get<std::string>() << "\n";
    }
}

static void deleteExpense(api::ApiClient& client) {
    std::string expenseId;
    std::cout << "Expense ID to delete: ";
    std::getline(std::cin, expenseId);

    auto result = client.del("/api/expenses/" + expenseId);
    if (result["success"].get<bool>()) {
        std::cout << "Expense deleted.\n";
    } else {
        std::cout << "Error: " << result["error"].get<std::string>() << "\n";
    }
}

void showExpenseScreen(api::ApiClient& client) {
    while (true) {
        std::cout << "\n===== EXPENSES =====\n";
        std::cout << "1. List expenses\n";
        std::cout << "2. Add expense\n";
        std::cout << "3. Delete expense\n";
        std::cout << "4. Back\n";
        std::cout << "Choice: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            listExpenses(client);
        } else if (choice == "2") {
            addExpense(client);
        } else if (choice == "3") {
            deleteExpense(client);
        } else if (choice == "4") {
            return;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

}