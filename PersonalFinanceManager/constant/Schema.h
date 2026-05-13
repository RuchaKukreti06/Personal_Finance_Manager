#ifndef CONSTANT_SCHEMA_H
#define CONSTANT_SCHEMA_H

namespace finance
{
constexpr const char* DATABASE_SCHEMA = R"(
CREATE TABLE IF NOT EXISTS expenses (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    date TEXT NOT NULL,
    category TEXT NOT NULL,
    amount REAL NOT NULL,
    description TEXT
);

CREATE TABLE IF NOT EXISTS income (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    date TEXT NOT NULL,
    source TEXT NOT NULL,
    amount REAL NOT NULL,
    description TEXT
);

CREATE TABLE IF NOT EXISTS budgets (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    category TEXT NOT NULL UNIQUE,
    amount REAL NOT NULL,
    period TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    password_hash TEXT NOT NULL
);
)";

constexpr int MIN_PASSWORD_LENGTH = 6;
constexpr int MAX_DESCRIPTION_LENGTH = 500;
constexpr double MIN_AMOUNT = 0.01;

} // namespace finance

#endif // CONSTANT_SCHEMA_H
