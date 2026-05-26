#ifndef FINANCE_CLIENT_SCREENS_LOGINSCREEN_H
#define FINANCE_CLIENT_SCREENS_LOGINSCREEN_H

#include <ftxui/component/component.hpp>
#include <functional>

namespace screens {

ftxui::Component LoginScreen(
    std::function<void()> onLoginSuccess,
    std::function<void()> onGoToRegister);

}

#endif
