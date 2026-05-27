#include "repositories/UserRepository.h"
#include "database/Database.h"
#include <spdlog/spdlog.h>

namespace repositories {

std::optional<User> UserRepository::findByUsername(const std::string& username) {
    auto& session = database::Database::instance().getSession();
    auto result = session.sql(
        "SELECT id, username, email, password_hash, created_at FROM finance_db.users WHERE username = ?")
        .bind(username)
        .execute();

    auto row = result.fetchOne();
    if (!row) return std::nullopt;

    User user;
    user.id = row[0].get<int>();
    user.username = row[1].get<std::string>();
    user.email = row[2].get<std::string>();
    user.passwordHash = row[3].get<std::string>();
    user.createdAt = row[4].get<std::string>();
    return user;
}

std::optional<User> UserRepository::findByEmail(const std::string& email) {
    auto& session = database::Database::instance().getSession();
    auto result = session.sql(
        "SELECT id, username, email, password_hash, created_at FROM finance_db.users WHERE email = ?")
        .bind(email)
        .execute();

    auto row = result.fetchOne();
    if (!row) return std::nullopt;

    User user;
    user.id = row[0].get<int>();
    user.username = row[1].get<std::string>();
    user.email = row[2].get<std::string>();
    user.passwordHash = row[3].get<std::string>();
    user.createdAt = row[4].get<std::string>();
    return user;
}

std::optional<User> UserRepository::findById(int id) {
    auto& session = database::Database::instance().getSession();
    auto result = session.sql(
        "SELECT id, username, email, password_hash, created_at FROM finance_db.users WHERE id = ?")
        .bind(id)
        .execute();

    auto row = result.fetchOne();
    if (!row) return std::nullopt;

    User user;
    user.id = row[0].get<int>();
    user.username = row[1].get<std::string>();
    user.email = row[2].get<std::string>();
    user.passwordHash = row[3].get<std::string>();
    user.createdAt = row[4].get<std::string>();
    return user;
}

bool UserRepository::create(const User& user) {
    try {
        auto& session = database::Database::instance().getSession();
        session.sql(
            "INSERT INTO finance_db.users (username, email, password_hash) VALUES (?, ?, ?)")
            .bind(user.username)
            .bind(user.email)
            .bind(user.passwordHash)
            .execute();
        return true;
    } catch (const std::exception& e) {
        spdlog::error("UserRepository::create failed: {}", e.what());
        return false;
    }
}

bool UserRepository::existsByUsername(const std::string& username) {
    auto& session = database::Database::instance().getSession();
    auto result = session.sql(
        "SELECT COUNT(*) FROM finance_db.users WHERE username = ?")
        .bind(username)
        .execute();

    auto row = result.fetchOne();
    return row && row[0].get<int>() > 0;
}

bool UserRepository::existsByEmail(const std::string& email) {
    auto& session = database::Database::instance().getSession();
    auto result = session.sql(
        "SELECT COUNT(*) FROM finance_db.users WHERE email = ?")
        .bind(email)
        .execute();

    auto row = result.fetchOne();
    return row && row[0].get<int>() > 0;
}

}
