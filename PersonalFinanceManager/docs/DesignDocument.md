# Personal Finance Manager Design Document

## 1. Overview
The Personal Finance Manager is a console-based application for tracking expenses, income, and budgets with SQLite persistence. Its design emphasizes clean architecture, separation of concerns, and extensibility.

## 2. Goals
- Maintain clear separation between UI, business logic, and persistence
- Support expense and income recording, filtering, and deletion
- Filter expenses by category and date range
- Track budgets and provide dashboard-style summary insight with budget status
- Persist data across restarts using SQLite
- Keep validation centralized and behavior predictable

## 3. Architecture
The system is organized into the following layers:

- **Database**: Responsible for SQLite connection management and schema initialization.
- **Repository**: Encapsulates CRUD operations for expenses, income, and budgets.
- **Service**: Implements business rules, validation, and summary calculations.
- **UI**: Handles user interaction, input prompts, and command dispatch.

## 4. Data Model
The core entities are:
- `Expense` — date, category, amount, optional description
- `Income` — date, source, amount, optional description
- `Budget` — category, amount, period

### Database tables
- `expenses(id, date, category, amount, description)`
- `income(id, date, source, amount, description)`
- `budgets(id, category, amount, period)`

## 5. UML Diagrams

### 5.1 Use Case Diagram
```mermaid
%%{init: {"theme": "base"}}%%
flowchart TD
    User[User]
    Authenticate((Authenticate / Login))
    AddExpense((Add Expense))
    ViewExpenses((View Expenses))
    FilterExpenses((Filter Expenses by Category, Date, Range))
    DeleteExpense((Delete Expense))
    AddIncome((Add Income))
    ViewIncome((View Income))
    CreateBudget((Create Budget / Allocate Budget))
    ViewBudgets((View Budgets))
    Dashboard((Dashboard Summary))

    User --> Authenticate
    Authenticate --> AddExpense
    Authenticate --> ViewExpenses
    Authenticate --> FilterExpenses
    Authenticate --> DeleteExpense
    Authenticate --> AddIncome
    Authenticate --> ViewIncome
    Authenticate --> CreateBudget
    Authenticate --> ViewBudgets
    Authenticate --> Dashboard
```

### 5.2 Flow Diagram
```mermaid
flowchart TD
    Start([App Start]) --> Auth["Authenticate / Login"]
    Auth --> Menu["Show Main Menu"]
    Menu -->|1| AddExpense["Add Expense"]
    Menu -->|2| ViewExpenses["View Expenses"]
    Menu -->|3| FilterExpenses["Filter Expenses"]
    Menu -->|4| DeleteExpense["Delete Expense"]
    Menu -->|5| AddIncome["Add Income"]
    Menu -->|6| ViewIncome["View Income"]
    Menu -->|7| SetBudget["Set Budget"]
    Menu -->|8| ViewBudgets["View Budgets"]
    Menu -->|9| Dashboard["View Dashboard"]
    Menu -->|0| Exit([Exit])
    AddExpense --> Menu
    ViewExpenses --> Menu
    FilterExpenses --> Menu
    DeleteExpense --> Menu
    AddIncome --> Menu
    ViewIncome --> Menu
    SetBudget --> Menu
    ViewBudgets --> Menu
    Dashboard --> Menu
```

### 5.3 Activity Diagram
```mermaid
flowchart TD
    Start([App Launch]) --> Auth["Authenticate / Login"]
    Auth --> Menu["Show Main Menu"]

    Menu --> Expense["Add Expense"]
    Menu --> Income["Add Income"]
    Menu --> Budget["Set Budget / Allocate Budget"]
    Menu --> Filter["Filter Expenses"]
    Menu --> Dashboard["View Dashboard"]

    Expense --> ExpenseInput["Enter Date / Category / Amount / Description"]
    ExpenseInput --> ValidateExpense["Validate Date, Category, Amount"]
    ValidateExpense --> SaveExpense["Save Expense Record"]
    SaveExpense --> Menu

    Income --> IncomeInput["Enter Date / Source / Amount / Description"]
    IncomeInput --> ValidateIncome["Validate Date, Source, Amount"]
    ValidateIncome --> SaveIncome["Save Income Record"]
    SaveIncome --> Menu

    Budget --> BudgetInput["Enter Category / Amount / Period"]
    BudgetInput --> ValidateBudget["Validate Budget Fields"]
    ValidateBudget --> SaveBudget["Save or Update Budget"]
    SaveBudget --> Menu

    Filter --> CategoryFilter["Filter by Category"]
    Filter --> DateRangeFilter["Filter by Date or Range"]
    CategoryFilter --> ShowFiltered["Display Filtered Expenses"]
    DateRangeFilter --> ShowFiltered
    ShowFiltered --> Menu

    Dashboard --> ComputeSummary["Calculate Income, Expenses, Balance"]
    ComputeSummary --> CompareBudgets["Compare Budget vs Spent"]
    CompareBudgets --> Menu
```

### 5.4 ER Diagram
```mermaid
erDiagram
    EXPENSES {
      INTEGER id PK
      TEXT date
      TEXT category
      REAL amount
      TEXT description
    }
    INCOME {
      INTEGER id PK
      TEXT date
      TEXT source
      REAL amount
      TEXT description
    }
    BUDGET {
      INTEGER id PK
      TEXT category
      REAL amount
      TEXT period
    }
    BUDGET ||--o{ EXPENSES : "tracks spending"
```

### 5.5 Class Diagram
```mermaid
classDiagram
    class Database {
      +Database(string path)
      +executeSchema()
      +connection() : sqlite3*
    }
    class ExpenseRepository {
      +add(expense : Expense) : int
      +list() : List<Expense>
      +filter(category : string, startDate : string, endDate : string) : List<Expense>
      +remove(expenseId : int) : bool
    }
    class IncomeRepository {
      +add(income : Income) : int
      +list() : List<Income>
    }
    class BudgetRepository {
      +addOrReplace(budget : Budget) : int
      +list() : List<Budget>
      +findByCategory(category : string) : Budget?
    }
    class FinanceService {
      +addExpense(date : string, category : string, amount : double, description : string) : int
      +addIncome(date : string, source : string, amount : double, description : string) : int
      +addBudget(category : string, amount : double, period : string) : int
      +deleteExpense(expenseId : int) : bool
      +listExpenses() : List<Expense>
      +filterExpenses(category : string, startDate : string, endDate : string) : List<Expense>
      +listIncome() : List<Income>
      +listBudgets() : List<Budget>
      +getSummary() : Summary
      +validateDate(date : string)
      +validateAmount(amount : double)
      +validateText(value : string, fieldName : string)
    }
    class FinanceUI {
      +run()
      +addExpenseFlow()
      +addIncomeFlow()
      +addBudgetFlow()
      +filterExpensesFlow()
      +deleteExpenseFlow()
      +showSummary(summary : Summary)
      +showDashboard(summary : Summary)
    }

    Database <|-- ExpenseRepository
    Database <|-- IncomeRepository
    Database <|-- BudgetRepository
    ExpenseRepository --> FinanceService
    IncomeRepository --> FinanceService
    BudgetRepository --> FinanceService
    FinanceService --> FinanceUI
```

## 6. Design Principles
- **Single Responsibility**: Each class handles one layer of concern.
- **Separation of Concerns**: UI is separate from business logic and persistence.
- **Modularity**: Repositories and services are interchangeable and easy to extend.
- **Validation-first**: All input is validated before persistence.
- **Persistence Layer**: SQLite is isolated behind `Database` and repository classes.
- **Extensibility**: New reports, export targets, or UI modes can be added without changing core services.

## 7. Recommended Document Use
- Insert the Mermaid blocks directly into markdown or documentation tools that support Mermaid.
- Use the use case diagram for stakeholder requirements.
- Use the flow and activity diagrams for implementation planning.
- Use the ER diagram to describe the database schema.
- Use the class diagram to explain the code structure.
