#ifndef DASHBOARDSCREEN_H
#define DASHBOARDSCREEN_H

#include <ftxui/component/component.hpp>
#include <functional>

namespace screens {

ftxui::Component DashboardScreen(std::function<void()> onLogout);

}

#endif
