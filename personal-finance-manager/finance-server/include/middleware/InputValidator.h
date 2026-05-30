#ifndef FINANCE_SERVER_MIDDLEWARE_INPUTVALIDATOR_H
#define FINANCE_SERVER_MIDDLEWARE_INPUTVALIDATOR_H

#include <nlohmann/json.hpp>
#include <httplib.h>
#include <string>
#include <vector>

namespace middleware {

class InputValidator {
public:
    static bool hasRequiredFields(const nlohmann::json& body, const std::vector<std::string>& fields);
    static bool parseJsonBody(const httplib::Request& request, nlohmann::json& outBody, httplib::Response& response);
};

}

#endif
