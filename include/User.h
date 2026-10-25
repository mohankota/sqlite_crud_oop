#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

class User {
private:
    int id;
    std::string name;
    std::string email;
    int age;

public:
    User();
    User(int id, const std::string& name, const std::string& email, int age);

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getEmail() const;
    int getAge() const;

    // Setters
    void setId(int id);
    void setName(const std::string& name);
    void setEmail(const std::string& email);
    void setAge(int age);

    void display() const;
};

#endif // USER_H
