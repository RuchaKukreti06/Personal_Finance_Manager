#include "screens/LoginScreen.h"
#include "components/InputField.h"
#include "components/ErrorBox.h"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <memory>

namespace screens {

ftxui::Component LoginScreen(
    std::function<void()> onLoginSuccess,
    std::function<void()> onGoToRegister) {
    using namespace ftxui;

    auto username = std::make_shared<std::string>();
    auto password = std::make_shared<std::string>();
    auto error = std::make_shared<std::string>();

    auto usernameInput = ui::InputField(username.get(), "Username");
    auto passwordInput = ui::PasswordField(password.get(), "Password");

    auto loginBtn = Button(" Login ", [=] {
        if (username->empty() || password->empty()) {
            *error = "Username and password are required.";
            return;
        }
        if (username->length() < 3) {
            *error = "Username must be at least 3 characters.";
            return;
        }
        if (password->length() < 4) {
            *error = "Password must be at least 4 characters.";
            return;
        }
        *error = "";
        onLoginSuccess();
    }, ButtonOption::Animated(Color::Green));

    auto registerBtn = Button(" Register Instead ", [=] {
        *error = "";
        onGoToRegister();
    }, ButtonOption::Simple());

    auto container = Container::Vertical({
        usernameInput,
        passwordInput,
        loginBtn,
        registerBtn,
    });

    return Renderer(container, [=] {
        return vbox({
            text("╔═══════════════════════════════════╗") | color(Color::Cyan),
            text("║    Personal Finance Manager       ║") | color(Color::Cyan),
            text("╚═══════════════════════════════════╝") | color(Color::Cyan),
            separator(),
            text("  Login") | bold,
            text(""),
            hbox({text("  Username: "), usernameInput->Render()}),
            text(""),
            hbox({text("  Password: "), passwordInput->Render()}),
            text(""),
            ui::ErrorBox(*error),
            text(""),
            hbox({text("  "), loginBtn->Render(), text("  "), registerBtn->Render()}),
        }) | border | center;
    });
}

}
