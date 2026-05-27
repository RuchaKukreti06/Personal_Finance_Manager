#include "utils/Logger.h"
#include "utils/Constants.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <vector>
#include <memory>

namespace utils {

void Logger::init(const std::string& level, const std::string& filePath) {
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        filePath, constants::logger::MAX_FILE_SIZE, constants::logger::MAX_FILES);

    std::vector<spdlog::sink_ptr> sinks{consoleSink, fileSink};
    auto logger = std::make_shared<spdlog::logger>(
        constants::logger::NAME, sinks.begin(), sinks.end());

    logger->set_pattern(constants::logger::PATTERN);

    if (level == "debug") logger->set_level(spdlog::level::debug);
    else if (level == "warn") logger->set_level(spdlog::level::warn);
    else if (level == "error") logger->set_level(spdlog::level::err);
    else logger->set_level(spdlog::level::info);

    spdlog::set_default_logger(logger);
    spdlog::info("Logger initialized [level={}]", level);
}

}
