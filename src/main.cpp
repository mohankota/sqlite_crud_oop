#include "Database.h"
#include "UserRepository.h"
#include "Menu.h"
#include <iostream>

int main() {
    Database db("users.db");

    if (!db.open()) {
        return 1;
    }

    UserRepository repo(db);
    repo.createTable();

    Menu menu(repo);
    menu.run();

    return 0;
}
