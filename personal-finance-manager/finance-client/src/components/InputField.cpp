#include "InputField.h"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

namespace ui {

ftxui::Component InputField(std::string* content, const std::string& placeholder) {
    using namespace ftxui;
    auto option = InputOption::Default();
    option.placeholder = placeholder;
    return Input(content, option) | borderLight | size(WIDTH, EQUAL, 40);
}

ftxui::Component PasswordField(std::string* content, const std::string& placeholder) {
    using namespace ftxui;
    auto option = InputOption::Default();
    option.placeholder = placeholder;
    option.password = true;
    return Input(content, option) | borderLight | size(WIDTH, EQUAL, 40);
}

}
