#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include "Database.h"
#include "User.h"
#include <vector>

class UserRepository {
private:
    Database& database;

public:
    UserRepository(Database& db);

    void createTable();
    bool insert(const User& user);
    std::vector<User> getAll();
    bool update(const User& user);
    bool remove(int id);
};

#endif // USER_REPOSITORY_H
