#include <gtest/gtest.h>
#include "User.h"

// ---------- Default constructor ----------
TEST(UserTest, DefaultConstructor) {
    User u;
    EXPECT_EQ(u.getId(), 0);
    EXPECT_EQ(u.getName(), "");
    EXPECT_EQ(u.getEmail(), "");
    EXPECT_EQ(u.getAge(), 0);
}

// ---------- Parameterized constructor ----------
TEST(UserTest, ParameterizedConstructor) {
    User u(1, "Alice", "alice@example.com", 28);
    EXPECT_EQ(u.getId(), 1);
    EXPECT_EQ(u.getName(), "Alice");
    EXPECT_EQ(u.getEmail(), "alice@example.com");
    EXPECT_EQ(u.getAge(), 28);
}

// ---------- Setters ----------
TEST(UserTest, Setters) {
    User u;
    u.setId(10);
    u.setName("Bob");
    u.setEmail("bob@test.com");
    u.setAge(35);

    EXPECT_EQ(u.getId(), 10);
    EXPECT_EQ(u.getName(), "Bob");
    EXPECT_EQ(u.getEmail(), "bob@test.com");
    EXPECT_EQ(u.getAge(), 35);
}

// ---------- Display does not crash ----------
TEST(UserTest, DisplayDoesNotCrash) {
    User u(5, "Carol", "carol@mail.com", 22);
    testing::internal::CaptureStdout();
    u.display();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Carol"), std::string::npos);
}
