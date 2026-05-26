#include "components/Navbar.h"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

namespace ui {

ftxui::Component Navbar(int* selected, std::function<void()> onLogout) {
    using namespace ftxui;

    auto menuOption = MenuOption::HorizontalAnimated();
    menuOption.entries_option.transform = [](const EntryState& state) {
        Element e = text(state.label) | center;
        if (state.focused) {
            e = e | inverted;
        }
        return e | size(WIDTH, EQUAL, 14);
    };

    static std::vector<std::string> entries = {
        "Dashboard", "Expenses", "Income", "Budgets", "Summary"
    };

    auto menu = Menu(&entries, selected, menuOption);
    auto logoutBtn = Button(" Logout ", onLogout, ButtonOption::Simple());

    return Container::Horizontal({menu, logoutBtn}) | Renderer([=](Element inner) {
        return hbox({
            inner,
        }) | border;
    });
}

}
