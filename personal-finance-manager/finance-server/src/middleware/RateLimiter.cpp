#include "middleware/RateLimiter.h"
#include "utils/Constants.h"
#include <spdlog/spdlog.h>

namespace middleware {

RateLimiter& RateLimiter::instance() {
    static RateLimiter inst;
    return inst;
}

bool RateLimiter::isAllowed(const std::string& clientIp) {
    std::lock_guard<std::mutex> lock(mutex_);

    auto now = std::chrono::steady_clock::now();
    auto& record = clients_[clientIp];

    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - record.windowStart).count();

    if (elapsed >= constants::ratelimit::WINDOW_SECONDS) {
        record.requestCount = 1;
        record.windowStart = now;
        return true;
    }

    record.requestCount++;

    if (record.requestCount > constants::ratelimit::MAX_REQUESTS_PER_WINDOW) {
        spdlog::warn("Rate limit exceeded for IP: {}", clientIp);
        return false;
    }

    return true;
}

}
