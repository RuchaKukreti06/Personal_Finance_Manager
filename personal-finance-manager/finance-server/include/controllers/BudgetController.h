#ifndef FINANCE_SERVER_CONTROLLERS_BUDGETCONTROLLER_H
#define FINANCE_SERVER_CONTROLLERS_BUDGETCONTROLLER_H

#include <httplib.h>

namespace controllers {

class BudgetController {
public:
    static void registerRoutes(httplib::Server& server);

private:
    static void handleGetBudgets(const httplib::Request& request, httplib::Response& response);
    static void handleAddBudget(const httplib::Request& request, httplib::Response& response);
    static void handleUpdateBudget(const httplib::Request& request, httplib::Response& response);
    static void handleDeleteBudget(const httplib::Request& request, httplib::Response& response);
    static void handleCheckAlerts(const httplib::Request& request, httplib::Response& response);
};

}

#endif
