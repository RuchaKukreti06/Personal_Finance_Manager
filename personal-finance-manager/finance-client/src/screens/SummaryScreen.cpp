#include "screens/SummaryScreen.h"
#include <iostream>
#include <string>

namespace screens {

void showSummaryScreen(api::ApiClient& client) {
    std::string month, year;

    std::cout << "\n===== MONTHLY SUMMARY =====\n";
    std::cout << "Month (1-12): ";
    std::getline(std::cin, month);
    std::cout << "Year: ";
    std::getline(std::cin, year);

    auto summary = client.get("/api/summary/monthly?month=" + month + "&year=" + year);
    if (!summary["success"].get<bool>()) {
        std::cout << "Error: " << summary["error"].get<std::string>() << "\n";
        return;
    }

    std::cout << "\n--- Summary for " << month << "/" << year << " ---\n";
    std::cout << "Total Income:  $" << summary["totalIncome"] << "\n";
    std::cout << "Total Expense: $" << summary["totalExpense"] << "\n";
    std::cout << "Balance:       $" << summary["balance"] << "\n";
    std::cout << "Transactions:  " << summary["transactionCount"] << "\n";

    auto breakdown = client.get("/api/summary/category?month=" + month + "&year=" + year);
    if (breakdown["success"].get<bool>() && !breakdown["categories"].empty()) {
        std::cout << "\n--- Category Breakdown ---\n";
        for (const auto& cat : breakdown["categories"]) {
            std::cout << cat["category"].get<std::string>() << ": $"
                      << cat["total"] << " (" << cat["percentage"] << "%)\n";
        }
    }
}

}