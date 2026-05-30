#include "utils/DateUtils.h"
#include "utils/Constants.h"
#include <sstream>
#include <iomanip>

namespace utils {

static bool isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int getLastDayOfMonth(int month, int year) {
    static constexpr int DAYS_IN_MONTH[] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    if (month < constants::validation::MIN_MONTH ||
        month > constants::validation::MAX_MONTH) return 0;

    int days = DAYS_IN_MONTH[month - 1];

    if (month == constants::date::FEBRUARY && isLeapYear(year)) {
        days = constants::date::LEAP_DAY;
    }

    return days;
}

std::pair<std::string, std::string> getMonthDateRange(int month, int year) {
    std::ostringstream startSs, endSs;

    startSs << year << constants::date::DATE_SEPARATOR
            << std::setw(constants::date::DATE_WIDTH)
            << std::setfill(constants::date::DATE_PAD_CHAR) << month
            << constants::date::DATE_SEPARATOR
            << constants::date::MONTH_START_DAY;

    int lastDay = getLastDayOfMonth(month, year);
    endSs << year << constants::date::DATE_SEPARATOR
          << std::setw(constants::date::DATE_WIDTH)
          << std::setfill(constants::date::DATE_PAD_CHAR) << month
          << constants::date::DATE_SEPARATOR
          << std::setw(constants::date::DATE_WIDTH)
          << std::setfill(constants::date::DATE_PAD_CHAR) << lastDay;

    return {startSs.str(), endSs.str()};
}

}
