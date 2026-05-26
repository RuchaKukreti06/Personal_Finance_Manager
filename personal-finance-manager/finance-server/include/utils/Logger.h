#ifndef FINANCE_SERVER_UTILS_LOGGER_H
#define FINANCE_SERVER_UTILS_LOGGER_H

#include <string>
#include <spdlog/spdlog.h>

namespace utils {

class Logger {
public:
    static void init(const std::string& level, const std::string& filePath);
};

}

#endif
