#include "Database.h"
#include <iostream>

Database::Database(const std::string& name) : db(nullptr), dbName(name) {}

Database::~Database() {
    close();
}

bool Database::open() {
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    std::cout << "Database opened successfully.\n";
    return true;
}

void Database::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

sqlite3* Database::getConnection() {
    return db;
}

bool Database::execute(const std::string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}
