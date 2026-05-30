#include "middleware/InputValidator.h"

namespace middleware {

bool InputValidator::hasRequiredFields(const nlohmann::json& body, const std::vector<std::string>& fields) {
    for (const auto& field : fields) {
        if (!body.contains(field) || body[field].is_null()) {
            return false;
        }
    }
    return true;
}

bool InputValidator::parseJsonBody(const httplib::Request& request, nlohmann::json& outBody, httplib::Response& response) {
    if (request.body.empty()) {
        nlohmann::json error = {{"success", false}, {"error", "Request body is empty"}};
        response.status = 400;
        response.set_content(error.dump(), "application/json");
        return false;
    }

    try {
        outBody = nlohmann::json::parse(request.body);
        return true;
    } catch (const nlohmann::json::parse_error&) {
        nlohmann::json error = {{"success", false}, {"error", "Invalid JSON"}};
        response.status = 400;
        response.set_content(error.dump(), "application/json");
        return false;
    }
}

}
