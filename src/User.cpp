#include "User.h"

User::User() : id(0), age(0) {}

User::User(int id, const std::string& name, const std::string& email, int age)
    : id(id), name(name), email(email), age(age) {}

int User::getId() const { return id; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }
int User::getAge() const { return age; }

void User::setId(int id) { this->id = id; }
void User::setName(const std::string& name) { this->name = name; }
void User::setEmail(const std::string& email) { this->email = email; }
void User::setAge(int age) { this->age = age; }

void User::display() const {
    std::cout << id << "\t" << name << "\t\t" << email << "\t\t" << age << std::endl;
}
