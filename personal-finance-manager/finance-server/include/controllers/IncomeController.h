#ifndef FINANCE_SERVER_CONTROLLERS_INCOMECONTROLLER_H
#define FINANCE_SERVER_CONTROLLERS_INCOMECONTROLLER_H

#include <httplib.h>

namespace controllers {

class IncomeController {
public:
    static void registerRoutes(httplib::Server& server);

private:
    static void handleGetIncomes(const httplib::Request& request, httplib::Response& response);
    static void handleGetByDateRange(const httplib::Request& request, httplib::Response& response);
    static void handleAddIncome(const httplib::Request& request, httplib::Response& response);
    static void handleUpdateIncome(const httplib::Request& request, httplib::Response& response);
    static void handleDeleteIncome(const httplib::Request& request, httplib::Response& response);
};

}

#endif
