#include "screens/IncomeScreen.h"
#include <iostream>
#include <string>

namespace screens {

static void listIncomes(api::ApiClient& client) {
    auto result = client.get("/api/incomes");
    if (!result["success"].get<bool>()) {
        std::cout << "Error: " << result["error"].get<std::string>() << "\n";
        return;
    }
    auto incomes = result["incomes"];
    if (incomes.empty()) {
        std::cout << "No incomes found.\n";
        return;
    }
    std::cout << "\n--- Incomes ---\n";
    for (const auto& income : incomes) {
        std::cout << "[" << income["id"] << "] "
                  << income["date"].get<std::string>() << " | "
                  << income["source"].get<std::string>() << " | $"
                  << income["amount"] << " | "
                  << income["description"].get<std::string>() << "\n";
    }
}

static void addIncome(api::ApiClient& client) {
    std::string amount, source, description, date;

    std::cout << "Amount: ";
    std::getline(std::cin, amount);
    std::cout << "Source: ";
    std::getline(std::cin, source);
    std::cout << "Description: ";
    std::getline(std::cin, description);
    std::cout << "Date (YYYY-MM-DD): ";
    std::getline(std::cin, date);

    auto result = client.post("/api/incomes", {
        {"amount", std::stod(amount)},
        {"source", source},
        {"description", description},
        {"date", date}
    });

    if (result["success"].get<bool>()) {
        std::cout << "Income added.\n";
    } else {
        std::cout << "Error: " << result["error"].get<std::string>() << "\n";
    }
}

static void deleteIncome(api::ApiClient& client) {
    std::string incomeId;
    std::cout << "Income ID to delete: ";
    std::getline(std::cin, incomeId);

    auto result = client.del("/api/incomes/" + incomeId);
    if (result["success"].get<bool>()) {
        std::cout << "Income deleted.\n";
    } else {
        std::cout << "Error: " << result["error"].get<std::string>() << "\n";
    }
}

void showIncomeScreen(api::ApiClient& client) {
    while (true) {
        std::cout << "\n===== INCOMES =====\n";
        std::cout << "1. List incomes\n";
        std::cout << "2. Add income\n";
        std::cout << "3. Delete income\n";
        std::cout << "4. Back\n";
        std::cout << "Choice: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            listIncomes(client);
        } else if (choice == "2") {
            addIncome(client);
        } else if (choice == "3") {
            deleteIncome(client);
        } else if (choice == "4") {
            return;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

}