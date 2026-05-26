#include "Table.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>

namespace ui {

ftxui::Element Table(
    const std::vector<std::string>& headers,
    const std::vector<std::vector<std::string>>& rows) {
    using namespace ftxui;

    std::vector<std::vector<std::string>> tableData;
    tableData.push_back(headers);
    for (const auto& row : rows) {
        tableData.push_back(row);
    }

    auto table = ftxui::Table(tableData);

    table.SelectAll().Border(LIGHT);
    table.SelectRow(0).Decorate(bold);
    table.SelectRow(0).SeparatorVertical(LIGHT);
    table.SelectRow(0).Border(DOUBLE);

    return table.Render();
}

}
