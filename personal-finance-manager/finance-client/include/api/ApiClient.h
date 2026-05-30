#ifndef FINANCE_CLIENT_API_APICLIENT_H
#define FINANCE_CLIENT_API_APICLIENT_H

#include <nlohmann/json.hpp>
#include <string>

namespace api {

class ApiClient {
public:
    ApiClient(const std::string& host, int port);

    nlohmann::json post(const std::string& path, const nlohmann::json& body);
    nlohmann::json get(const std::string& path);
    nlohmann::json put(const std::string& path, const nlohmann::json& body);
    nlohmann::json del(const std::string& path);

    void setToken(const std::string& token);
    void clearToken();

private:
    std::string host_;
    int port_;
    std::string token_;
};

}

#endif