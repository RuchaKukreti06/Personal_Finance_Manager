#include "utils/ConfigLoader.h"
#include "utils/Logger.h"

#include <httplib.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <filesystem>

int main() {
    auto& config = utils::ConfigLoader::instance();
    config.load("config/config.json");

    std::filesystem::create_directories("logs");
    utils::Logger::init(config.logLevel(), config.logFile());

    httplib::Server server;

    server.Get("/health", [](const httplib::Request&, httplib::Response& res) {
        nlohmann::json body;
        body["status"] = "ok";
        res.set_content(body.dump(), "application/json");
    });

    spdlog::info("Starting server on {}:{}", config.serverHost(), config.serverPort());
    server.listen(config.serverHost(), config.serverPort());

    return 0;
}
