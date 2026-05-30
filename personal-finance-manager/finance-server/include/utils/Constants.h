#ifndef FINANCE_SERVER_UTILS_CONSTANTS_H
#define FINANCE_SERVER_UTILS_CONSTANTS_H

#include <cstddef>

namespace constants {

namespace logger {
    constexpr const char* NAME = "server";
    constexpr const char* PATTERN = "[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%s:%#] %v";
    constexpr std::size_t MAX_FILE_SIZE = 1024 * 1024 * 5;
    constexpr std::size_t MAX_FILES = 3;
}

namespace auth {
    constexpr int MIN_PASSWORD_LENGTH = 8;
}

namespace budget {
    constexpr double WARNING_THRESHOLD = 80.0;
    constexpr double EXCEEDED_THRESHOLD = 100.0;
    constexpr const char* LEVEL_OK = "ok";
    constexpr const char* LEVEL_WARNING = "warning";
    constexpr const char* LEVEL_EXCEEDED = "exceeded";
}

namespace validation {
    constexpr int MIN_MONTH = 1;
    constexpr int MAX_MONTH = 12;
    constexpr int MIN_YEAR = 2000;
    constexpr double PERCENTAGE_MULTIPLIER = 100.0;
}

namespace date {
    constexpr int FEBRUARY = 2;
    constexpr int LEAP_DAY = 29;
    constexpr int DATE_WIDTH = 2;
    constexpr char DATE_SEPARATOR = '-';
    constexpr const char* MONTH_START_DAY = "01";
    constexpr char DATE_PAD_CHAR = '0';
}

namespace ratelimit {
    constexpr int MAX_REQUESTS_PER_WINDOW = 100;
    constexpr int WINDOW_SECONDS = 60;
}

}

#endif
