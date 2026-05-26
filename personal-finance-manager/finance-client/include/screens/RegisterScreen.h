#ifndef REGISTERSCREEN_H
#define REGISTERSCREEN_H

#include <ftxui/component/component.hpp>
#include <functional>

namespace screens {

ftxui::Component RegisterScreen(
    std::function<void()> onRegisterSuccess,
    std::function<void()> onGoToLogin);

}

#endif
