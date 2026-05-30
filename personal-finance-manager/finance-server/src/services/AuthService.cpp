#include "services/AuthService.h"
#include "repositories/UserRepository.h"
#include "auth/PasswordHasher.h"
#include "auth/JwtManager.h"
#include "utils/JsonSerializer.h"
#include "utils/Constants.h"
#include <spdlog/spdlog.h>

namespace services {

nlohmann::json AuthService::registerUser(const std::string& username, const std::string& email, const std::string& password) {
    repositories::UserRepository repo;

    if (username.empty() || email.empty() || password.empty()) {
        return {{"success", false}, {"error", "All fields are required"}};
    }
    if (password.length() < constants::auth::MIN_PASSWORD_LENGTH) {
        return {{"success", false}, {"error", "Password must be at least 8 characters"}};
    }
    if (repo.existsByUsername(username)) {
        return {{"success", false}, {"error", "Username already exists"}};
    }
    if (repo.existsByEmail(email)) {
        return {{"success", false}, {"error", "Email already exists"}};
    }

    User user;
    user.username = username;
    user.email = email;
    user.passwordHash = auth::PasswordHasher::hash(password);

    if (!repo.create(user)) {
        return {{"success", false}, {"error", "Failed to create account"}};
    }

    spdlog::info("User registered: {}", username);
    return {{"success", true}, {"message", "Account created successfully"}};
}

nlohmann::json AuthService::login(const std::string& username, const std::string& password) {
    repositories::UserRepository repo;

    auto user = repo.findByUsername(username);
    if (!user) {
        return {{"success", false}, {"error", "Invalid username or password"}};
    }
    if (!auth::PasswordHasher::verify(password, user->passwordHash)) {
        return {{"success", false}, {"error", "Invalid username or password"}};
    }

    auto token = auth::JwtManager::instance().generate(user->id, user->username);
    spdlog::info("User logged in: {}", username);

    return {
        {"success", true},
        {"token", token},
        {"user", serializer::toJson(*user)}
    };
}

nlohmann::json AuthService::changePassword(int userId, const std::string& oldPassword, const std::string& newPassword) {
    repositories::UserRepository repo;

    auto user = repo.findById(userId);
    if (!user) {
        return {{"success", false}, {"error", "User not found"}};
    }
    if (!auth::PasswordHasher::verify(oldPassword, user->passwordHash)) {
        return {{"success", false}, {"error", "Current password is incorrect"}};
    }
    if (newPassword.length() < constants::auth::MIN_PASSWORD_LENGTH) {
        return {{"success", false}, {"error", "New password must be at least 8 characters"}};
    }

    std::string newHash = auth::PasswordHasher::hash(newPassword);

    if (!repo.updatePassword(userId, newHash)) {
        return {{"success", false}, {"error", "Failed to update password"}};
    }

    spdlog::info("Password changed for user: {}", user->username);
    return {{"success", true}, {"message", "Password changed successfully"}};
}

}
