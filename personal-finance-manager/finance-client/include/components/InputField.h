#ifndef INPUTFIELD_H
#define INPUTFIELD_H

#include <string>
#include <ftxui/component/component.hpp>

namespace ui {

ftxui::Component InputField(std::string* content, const std::string& placeholder);
ftxui::Component PasswordField(std::string* content, const std::string& placeholder);

}

#endif
