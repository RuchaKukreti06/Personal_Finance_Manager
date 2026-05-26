#include "screens/LoginScreen.h"
#include "screens/RegisterScreen.h"
#include "screens/DashboardScreen.h"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

enum class AppScreen {
    Login,
    Register,
    Dashboard,
};

int main() {
    using namespace ftxui;

    auto screen = ScreenInteractive::Fullscreen();
    auto currentScreen = std::make_shared<AppScreen>(AppScreen::Login);

    auto goToLogin = [&] { *currentScreen = AppScreen::Login; };
    auto goToRegister = [&] { *currentScreen = AppScreen::Register; };
    auto goToDashboard = [&] { *currentScreen = AppScreen::Dashboard; };
    auto logout = [&] { *currentScreen = AppScreen::Login; };

    auto loginScreen = screens::LoginScreen(goToDashboard, goToRegister);
    auto registerScreen = screens::RegisterScreen(goToLogin, goToLogin);
    auto dashboardScreen = screens::DashboardScreen(logout);

    auto container = Container::Tab({
        loginScreen,
        registerScreen,
        dashboardScreen,
    }, nullptr);

    auto renderer = Renderer(container, [&] {
        switch (*currentScreen) {
            case AppScreen::Login:
                return loginScreen->Render();
            case AppScreen::Register:
                return registerScreen->Render();
            case AppScreen::Dashboard:
                return dashboardScreen->Render();
        }
        return text("Error") | center;
    });

    auto mainComponent = CatchEvent(renderer, [&](Event event) {
        switch (*currentScreen) {
            case AppScreen::Login:
                return loginScreen->OnEvent(event);
            case AppScreen::Register:
                return registerScreen->OnEvent(event);
            case AppScreen::Dashboard:
                return dashboardScreen->OnEvent(event);
        }
        return false;
    });

    screen.Loop(mainComponent);
    return 0;
}
