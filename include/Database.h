#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "sqlite3.h"

class Database {
private:
    sqlite3* db;
    std::string dbName;

public:
    Database(const std::string& name = "users.db");
    ~Database();

    bool open();
    void close();
    sqlite3* getConnection();
    bool execute(const std::string& sql);
};

#endif // DATABASE_H
