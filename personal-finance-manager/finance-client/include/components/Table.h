#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <ftxui/dom/elements.hpp>

namespace ui {

ftxui::Element Table(
    const std::vector<std::string>& headers,
    const std::vector<std::vector<std::string>>& rows);

}

#endif
