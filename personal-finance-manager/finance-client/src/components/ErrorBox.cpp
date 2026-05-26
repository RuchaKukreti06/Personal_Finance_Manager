#include "ErrorBox.h"

#include <ftxui/dom/elements.hpp>

namespace ui {

ftxui::Element ErrorBox(const std::string& message) {
    using namespace ftxui;
    if (message.empty()) {
        return text("");
    }
    return text(message) | color(Color::Red) | bold | border;
}

}
