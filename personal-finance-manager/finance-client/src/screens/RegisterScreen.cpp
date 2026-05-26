#include "screens/RegisterScreen.h"
#include "components/InputField.h"
#include "components/ErrorBox.h"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <memory>

namespace screens {

ftxui::Component RegisterScreen(
    std::function<void()> onRegisterSuccess,
    std::function<void()> onGoToLogin) {
    using namespace ftxui;

    auto username = std::make_shared<std::string>();
    auto email = std::make_shared<std::string>();
    auto password = std::make_shared<std::string>();
    auto confirmPass = std::make_shared<std::string>();
    auto error = std::make_shared<std::string>();

    auto usernameInput = ui::InputField(username.get(), "Username");
    auto emailInput = ui::InputField(email.get(), "Email");
    auto passwordInput = ui::PasswordField(password.get(), "Password");
    auto confirmInput = ui::PasswordField(confirmPass.get(), "Confirm Password");

    auto registerBtn = Button(" Register ", [=] {
        if (username->empty() || email->empty() || password->empty()) {
            *error = "All fields are required.";
            return;
        }
        if (username->length() < 3) {
            *error = "Username must be at least 3 characters.";
            return;
        }
        if (email->find('@') == std::string::npos) {
            *error = "Invalid email address.";
            return;
        }
        if (password->length() < 4) {
            *error = "Password must be at least 4 characters.";
            return;
        }
        if (*password != *confirmPass) {
            *error = "Passwords do not match.";
            return;
        }
        *error = "";
        onRegisterSuccess();
    }, ButtonOption::Animated(Color::Green));

    auto loginBtn = Button(" Back to Login ", [=] {
        *error = "";
        onGoToLogin();
    }, ButtonOption::Simple());

    auto container = Container::Vertical({
        usernameInput,
        emailInput,
        passwordInput,
        confirmInput,
        registerBtn,
        loginBtn,
    });

    return Renderer(container, [=] {
        return vbox({
            text("╔═══════════════════════════════════╗") | color(Color::Cyan),
            text("║    Personal Finance Manager       ║") | color(Color::Cyan),
            text("╚═══════════════════════════════════╝") | color(Color::Cyan),
            separator(),
            text("  Register") | bold,
            text(""),
            hbox({text("  Username: "), usernameInput->Render()}),
            text(""),
            hbox({text("  Email:    "), emailInput->Render()}),
            text(""),
            hbox({text("  Password: "), passwordInput->Render()}),
            text(""),
            hbox({text("  Confirm:  "), confirmInput->Render()}),
            text(""),
            ui::ErrorBox(*error),
            text(""),
            hbox({text("  "), registerBtn->Render(), text("  "), loginBtn->Render()}),
        }) | border | center;
    });
}

}
