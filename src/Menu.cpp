#include "Menu.h"
#include <iostream>
#include <limits>

Menu::Menu(UserRepository& repository) : repo(repository) {}

void Menu::insertUser() {
    std::string name, email;
    int age;

    std::cout << "\n--- Insert New User ---\n";
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    std::cout << "Enter email: ";
    std::getline(std::cin, email);
    std::cout << "Enter age: ";
    std::cin >> age;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    User user(0, name, email, age);
    repo.insert(user);
}

void Menu::displayUsers() {
    std::cout << "\n--- All Users ---\n";
    std::vector<User> users = repo.getAll();

    if (users.empty()) {
        std::cout << "No users found.\n";
        return;
    }

    std::cout << "ID\tName\t\tEmail\t\t\tAge\n";
    std::cout << "--------------------------------------------------------\n";
    for (const auto& user : users) {
        user.display();
    }
}

void Menu::updateUser() {
    int id, age;
    std::string name, email;

    std::cout << "\n--- Update User ---\n";
    std::cout << "Enter User ID to update: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter new name: ";
    std::getline(std::cin, name);
    std::cout << "Enter new email: ";
    std::getline(std::cin, email);
    std::cout << "Enter new age: ";
    std::cin >> age;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    User user(id, name, email, age);
    repo.update(user);
}

void Menu::deleteUser() {
    int id;
    std::cout << "\n--- Delete User ---\n";
    std::cout << "Enter User ID to delete: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    repo.remove(id);
}

void Menu::run() {
    int choice;
    do {
        std::cout << "\n========== SQLite CRUD Menu (OOP) ==========\n";
        std::cout << "1. Insert User\n";
        std::cout << "2. Display All Users\n";
        std::cout << "3. Update User\n";
        std::cout << "4. Delete User\n";
        std::cout << "5. Exit\n";
        std::cout << "============================================\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: insertUser();   break;
            case 2: displayUsers(); break;
            case 3: updateUser();   break;
            case 4: deleteUser();   break;
            case 5: std::cout << "Exiting program...\n"; break;
            default: std::cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);
}
