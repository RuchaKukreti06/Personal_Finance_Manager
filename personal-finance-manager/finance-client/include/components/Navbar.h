#ifndef NAVBAR_H
#define NAVBAR_H

#include <ftxui/component/component.hpp>
#include <functional>

namespace ui {

ftxui::Component Navbar(int* selected, std::function<void()> onLogout);

}

#endif
