#ifndef FINANCE_SERVER_CONTROLLERS_EXPENSECONTROLLER_H
#define FINANCE_SERVER_CONTROLLERS_EXPENSECONTROLLER_H

#include <httplib.h>

namespace controllers {

class ExpenseController {
public:
    static void registerRoutes(httplib::Server& server);

private:
    static void handleGetExpenses(const httplib::Request& request, httplib::Response& response);
    static void handleGetByDateRange(const httplib::Request& request, httplib::Response& response);
    static void handleGetByCategory(const httplib::Request& request, httplib::Response& response);
    static void handleAddExpense(const httplib::Request& request, httplib::Response& response);
    static void handleUpdateExpense(const httplib::Request& request, httplib::Response& response);
    static void handleDeleteExpense(const httplib::Request& request, httplib::Response& response);
};

}

#endif
