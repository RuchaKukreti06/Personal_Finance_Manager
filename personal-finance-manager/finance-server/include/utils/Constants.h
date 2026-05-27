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

}

#endif
