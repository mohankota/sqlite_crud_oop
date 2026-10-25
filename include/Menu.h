#ifndef MENU_H
#define MENU_H

#include "UserRepository.h"

class Menu {
private:
    UserRepository& repo;

    void insertUser();
    void displayUsers();
    void updateUser();
    void deleteUser();

public:
    Menu(UserRepository& repository);
    void run();
};

#endif // MENU_H
