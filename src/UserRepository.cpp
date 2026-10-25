#include "UserRepository.h"
#include <iostream>

UserRepository::UserRepository(Database& db) : database(db) {}

void UserRepository::createTable() {
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            email TEXT UNIQUE,
            age INTEGER
        );
    )";
    if (database.execute(sql)) {
        std::cout << "Table ready.\n";
    }
}

bool UserRepository::insert(const User& user) {
    const char* sql = "INSERT INTO users (name, email, age) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Prepare failed: " << sqlite3_errmsg(database.getConnection()) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, user.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, user.getEmail().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, user.getAge());

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    if (success) {
        std::cout << "User inserted successfully! (ID: "
                  << sqlite3_last_insert_rowid(database.getConnection()) << ")\n";
    } else {
        std::cerr << "Insert failed: " << sqlite3_errmsg(database.getConnection()) << std::endl;
    }

    sqlite3_finalize(stmt);
    return success;
}

std::vector<User> UserRepository::getAll() {
    std::vector<User> users;
    const char* sql = "SELECT id, name, email, age FROM users ORDER BY id;";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Prepare failed: " << sqlite3_errmsg(database.getConnection()) << std::endl;
        return users;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int age = sqlite3_column_int(stmt, 3);

        users.emplace_back(id, name, email, age);
    }

    sqlite3_finalize(stmt);
    return users;
}

bool UserRepository::update(const User& user) {
    const char* sql = "UPDATE users SET name = ?, email = ?, age = ? WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Prepare failed: " << sqlite3_errmsg(database.getConnection()) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, user.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, user.getEmail().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, user.getAge());
    sqlite3_bind_int(stmt, 4, user.getId());

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    if (success) {
        if (sqlite3_changes(database.getConnection()) > 0)
            std::cout << "User updated successfully!\n";
        else
            std::cout << "No user found with ID " << user.getId() << std::endl;
    } else {
        std::cerr << "Update failed: " << sqlite3_errmsg(database.getConnection()) << std::endl;
    }

    sqlite3_finalize(stmt);
    return success;
}

bool UserRepository::remove(int id) {
    const char* sql = "DELETE FROM users WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Prepare failed: " << sqlite3_errmsg(database.getConnection()) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    if (success) {
        if (sqlite3_changes(database.getConnection()) > 0)
            std::cout << "User deleted successfully!\n";
        else
            std::cout << "No user found with ID " << id << std::endl;
    } else {
        std::cerr << "Delete failed: " << sqlite3_errmsg(database.getConnection()) << std::endl;
    }

    sqlite3_finalize(stmt);
    return success;
}
