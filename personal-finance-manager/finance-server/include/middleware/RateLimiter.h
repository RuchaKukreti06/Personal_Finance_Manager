#ifndef FINANCE_SERVER_MIDDLEWARE_RATELIMITER_H
#define FINANCE_SERVER_MIDDLEWARE_RATELIMITER_H

#include <httplib.h>
#include <string>
#include <unordered_map>
#include <chrono>
#include <mutex>

namespace middleware {

class RateLimiter {
public:
    static RateLimiter& instance();
    bool isAllowed(const std::string& clientIp);

private:
    RateLimiter() = default;

    struct ClientRecord {
        int requestCount = 0;
        std::chrono::steady_clock::time_point windowStart;
    };

    std::unordered_map<std::string, ClientRecord> clients_;
    std::mutex mutex_;
};

}

#endif
