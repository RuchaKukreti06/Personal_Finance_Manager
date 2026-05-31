#include "screens/SummaryScreen.h"

#include <iostream>
#include <string>

namespace screens
{

void showSummaryScreen(api::ApiClient& client)
{
    while (true)
    {
        std::cout << "\n===== SUMMARY =====\n";
        std::cout << "1. Monthly Summary\n";
        std::cout << "2. Category Breakdown\n";
        std::cout << "3. Back\n";
        std::cout << "Choice: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "3") return;

        std::string month, year;
        std::cout << "Month (1-12): ";
        std::getline(std::cin, month);
        std::cout << "Year: ";
        std::getline(std::cin, year);

        if (choice == "1")
        {
            auto summary = client.get("/api/summary/monthly?month=" + month + "&year=" + year);
            if (!summary["success"].get<bool>())
            {
                std::cout << "Error: " << summary["error"].get<std::string>() << "\n";
                continue;
            }
            std::cout << "\n--- Summary for " << month << "/" << year << " ---\n";
            std::cout << "Total Income:  $" << summary["totalIncome"] << "\n";
            std::cout << "Total Expense: $" << summary["totalExpense"] << "\n";
            std::cout << "Balance:       $" << summary["balance"] << "\n";
            std::cout << "Transactions:  " << summary["transactionCount"] << "\n";
        }
        else if (choice == "2")
        {
            auto breakdown = client.get("/api/summary/categories?month=" + month + "&year=" + year);
            if (!breakdown["success"].get<bool>())
            {
                std::cout << "Error: " << breakdown["error"].get<std::string>() << "\n";
                continue;
            }
            std::cout << "\n--- Category Breakdown ---\n";
            if (breakdown["categories"].empty())
            {
                std::cout << "No expenses this month.\n";
            }
            else
            {
                for (const auto& cat : breakdown["categories"])
                {
                    std::cout << cat["category"].get<std::string>() << ": $" << cat["total"] << " ("
                              << cat["percentage"] << "%)\n";
                }
            }
        }
        else
        {
            std::cout << "Invalid choice.\n";
        }
    }
}

}