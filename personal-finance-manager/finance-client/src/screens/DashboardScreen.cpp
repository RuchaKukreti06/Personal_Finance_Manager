#include "DashboardScreen.h"
#include "components/Navbar.h"
#include "components/Table.h"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <memory>

namespace screens {

ftxui::Component DashboardScreen(std::function<void()> onLogout) {
    using namespace ftxui;

    auto tabIndex = std::make_shared<int>(0);
    auto navbar = ui::Navbar(tabIndex.get(), onLogout);

    std::vector<std::string> expenseHeaders = {"Date", "Category", "Amount", "Description"};
    std::vector<std::vector<std::string>> expenseRows = {
        {"2024-01-15", "Food", "$45.00", "Groceries"},
        {"2024-01-14", "Transport", "$12.50", "Uber ride"},
        {"2024-01-13", "Bills", "$89.99", "Electric bill"},
        {"2024-01-12", "Entertainment", "$15.00", "Movie tickets"},
        {"2024-01-11", "Food", "$32.00", "Restaurant"},
    };

    std::vector<std::string> incomeHeaders = {"Date", "Source", "Amount"};
    std::vector<std::vector<std::string>> incomeRows = {
        {"2024-01-01", "Salary", "$3,500.00"},
        {"2024-01-10", "Freelance", "$450.00"},
    };

    return Renderer(navbar, [=] {
        Element content;
        switch (*tabIndex) {
            case 0:
                content = vbox({
                    text(" Welcome to Personal Finance Manager") | bold,
                    separator(),
                    hbox({
                        vbox({
                            text(" Total Income: $3,950.00") | color(Color::Green),
                            text(" Total Expenses: $194.49") | color(Color::Red),
                            text(" Balance: $3,755.51") | color(Color::Cyan),
                        }) | border | flex,
                    }),
                    text(""),
                    text(" Recent Expenses:") | bold,
                    ui::Table(expenseHeaders, expenseRows),
                });
                break;
            case 1:
                content = vbox({
                    text(" Expenses") | bold,
                    separator(),
                    ui::Table(expenseHeaders, expenseRows),
                });
                break;
            case 2:
                content = vbox({
                    text(" Income") | bold,
                    separator(),
                    ui::Table(incomeHeaders, incomeRows),
                });
                break;
            case 3:
                content = vbox({
                    text(" Budgets") | bold,
                    separator(),
                    text(" (Budget tracking coming soon)") | dim,
                });
                break;
            case 4:
                content = vbox({
                    text(" Summary") | bold,
                    separator(),
                    text(" (Monthly summary coming soon)") | dim,
                });
                break;
            default:
                content = text("Unknown tab");
                break;
        }

        return vbox({
            navbar->Render(),
            content | flex,
        });
    });
}

} // namespace screens
