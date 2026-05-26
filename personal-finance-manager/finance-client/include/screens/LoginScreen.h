#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <ftxui/component/component.hpp>
#include <functional>

namespace screens {

ftxui::Component LoginScreen(
    std::function<void()> onLoginSuccess,
    std::function<void()> onGoToRegister);

}

#endif
