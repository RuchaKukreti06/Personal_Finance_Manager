#ifndef FINANCE_SERVER_UTILS_DATE_UTILS_H
#define FINANCE_SERVER_UTILS_DATE_UTILS_H

#include <string>
#include <utility>

namespace utils {

std::pair<std::string, std::string> getMonthDateRange(int month, int year);
int getLastDayOfMonth(int month, int year);

}

#endif
