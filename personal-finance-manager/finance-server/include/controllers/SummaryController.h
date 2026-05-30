#ifndef FINANCE_SERVER_CONTROLLERS_SUMMARYCONTROLLER_H
#define FINANCE_SERVER_CONTROLLERS_SUMMARYCONTROLLER_H

#include <httplib.h>

namespace controllers {

class SummaryController {
public:
    static void registerRoutes(httplib::Server& server);

private:
    static void handleMonthlySummary(const httplib::Request& request, httplib::Response& response);
    static void handleCategoryBreakdown(const httplib::Request& request, httplib::Response& response);
};

}

#endif
