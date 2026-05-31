#include "api/ApiClient.h"
#include <httplib.h>

namespace api {

ApiClient::ApiClient(const std::string& baseUrl) : baseUrl_(baseUrl) {}

void ApiClient::setToken(const std::string& token) {
    token_ = token;
}

void ApiClient::clearToken() {
    token_.clear();
}

nlohmann::json ApiClient::post(const std::string& path, const nlohmann::json& body) {
    httplib::Client client(baseUrl_);
    httplib::Headers headers;
    if (!token_.empty()) {
        headers.emplace("Authorization", "Bearer " + token_);
    }
    auto response = client.Post(path, headers, body.dump(), "application/json");
    if (!response) {
        return {{"success", false}, {"error", "Connection failed"}};
    }
    return nlohmann::json::parse(response->body);
}

nlohmann::json ApiClient::get(const std::string& path) {
    httplib::Client client(baseUrl_);
    httplib::Headers headers;
    if (!token_.empty()) {
        headers.emplace("Authorization", "Bearer " + token_);
    }
    auto response = client.Get(path, headers);
    if (!response) {
        return {{"success", false}, {"error", "Connection failed"}};
    }
    return nlohmann::json::parse(response->body);
}

nlohmann::json ApiClient::put(const std::string& path, const nlohmann::json& body) {
    httplib::Client client(baseUrl_);
    httplib::Headers headers;
    if (!token_.empty()) {
        headers.emplace("Authorization", "Bearer " + token_);
    }
    auto response = client.Put(path, headers, body.dump(), "application/json");
    if (!response) {
        return {{"success", false}, {"error", "Connection failed"}};
    }
    return nlohmann::json::parse(response->body);
}

nlohmann::json ApiClient::del(const std::string& path) {
    httplib::Client client(baseUrl_);
    httplib::Headers headers;
    if (!token_.empty()) {
        headers.emplace("Authorization", "Bearer " + token_);
    }
    auto response = client.Delete(path, headers);
    if (!response) {
        return {{"success", false}, {"error", "Connection failed"}};
    }
    return nlohmann::json::parse(response->body);
}

}