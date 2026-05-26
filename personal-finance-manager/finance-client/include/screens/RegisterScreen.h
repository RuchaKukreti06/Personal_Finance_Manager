#ifndef FINANCE_CLIENT_SCREENS_REGISTERSCREEN_H
#define FINANCE_CLIENT_SCREENS_REGISTERSCREEN_H

#include <ftxui/component/component.hpp>
#include <functional>

namespace screens {

ftxui::Component RegisterScreen(
    std::function<void()> onRegisterSuccess,
    std::function<void()> onGoToLogin);

}

#endif
