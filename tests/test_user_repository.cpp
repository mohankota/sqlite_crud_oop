#include <gtest/gtest.h>
#include "Database.h"
#include "UserRepository.h"
#include "User.h"
#include <vector>

// Helper: create a fresh in-memory database + repository for each test
class UserRepositoryTest : public ::testing::Test {
protected:
    Database* db;
    UserRepository* repo;

    void SetUp() override {
        // Use in-memory database so tests are isolated and fast
        db = new Database(":memory:");
        ASSERT_TRUE(db->open());
        repo = new UserRepository(*db);
        repo->createTable();
    }

    void TearDown() override {
        delete repo;
        delete db;
    }
};

// ---------- Table creation ----------
TEST_F(UserRepositoryTest, CreateTableSucceeds) {
    // Table already created in SetUp – just verify we can query it
    auto users = repo->getAll();
    EXPECT_TRUE(users.empty());
}

// ---------- Insert ----------
TEST_F(UserRepositoryTest, InsertUser) {
    User u(0, "Alice", "alice@example.com", 28);
    EXPECT_TRUE(repo->insert(u));

    auto users = repo->getAll();
    ASSERT_EQ(users.size(), 1);
    EXPECT_EQ(users[0].getName(), "Alice");
    EXPECT_EQ(users[0].getEmail(), "alice@example.com");
    EXPECT_EQ(users[0].getAge(), 28);
    EXPECT_GT(users[0].getId(), 0);   // auto-incremented
}

// ---------- Insert multiple ----------
TEST_F(UserRepositoryTest, InsertMultipleUsers) {
    EXPECT_TRUE(repo->insert(User(0, "Alice", "a@test.com", 20)));
    EXPECT_TRUE(repo->insert(User(0, "Bob",   "b@test.com", 30)));
    EXPECT_TRUE(repo->insert(User(0, "Carol", "c@test.com", 25)));

    auto users = repo->getAll();
    EXPECT_EQ(users.size(), 3);
}

// ---------- Unique email constraint ----------
TEST_F(UserRepositoryTest, DuplicateEmailFails) {
    EXPECT_TRUE(repo->insert(User(0, "Alice", "same@email.com", 20)));
    // Second insert with same email should fail
    EXPECT_FALSE(repo->insert(User(0, "Bob", "same@email.com", 30)));
}

// ---------- GetAll on empty table ----------
TEST_F(UserRepositoryTest, GetAllEmpty) {
    auto users = repo->getAll();
    EXPECT_TRUE(users.empty());
}

// ---------- Update ----------
TEST_F(UserRepositoryTest, UpdateUser) {
    repo->insert(User(0, "Alice", "alice@old.com", 20));
    auto users = repo->getAll();
    ASSERT_EQ(users.size(), 1);
    int id = users[0].getId();

    User updated(id, "Alice Updated", "alice@new.com", 21);
    EXPECT_TRUE(repo->update(updated));

    users = repo->getAll();
    ASSERT_EQ(users.size(), 1);
    EXPECT_EQ(users[0].getName(), "Alice Updated");
    EXPECT_EQ(users[0].getEmail(), "alice@new.com");
    EXPECT_EQ(users[0].getAge(), 21);
}

// ---------- Update non-existent ID ----------
TEST_F(UserRepositoryTest, UpdateNonExistent) {
    User fake(9999, "Ghost", "ghost@mail.com", 99);
    // update returns true (SQL succeeded) but changes() == 0
    // Our implementation still returns true; we just check no crash / no data
    repo->update(fake);
    auto users = repo->getAll();
    EXPECT_TRUE(users.empty());
}

// ---------- Delete ----------
TEST_F(UserRepositoryTest, DeleteUser) {
    repo->insert(User(0, "Alice", "a@test.com", 20));
    repo->insert(User(0, "Bob",   "b@test.com", 30));

    auto users = repo->getAll();
    ASSERT_EQ(users.size(), 2);
    int idToDelete = users[0].getId();

    EXPECT_TRUE(repo->remove(idToDelete));

    users = repo->getAll();
    ASSERT_EQ(users.size(), 1);
    EXPECT_EQ(users[0].getName(), "Bob");
}

// ---------- Delete non-existent ----------
TEST_F(UserRepositoryTest, DeleteNonExistent) {
    EXPECT_TRUE(repo->remove(9999));   // SQL succeeds, 0 rows affected
    auto users = repo->getAll();
    EXPECT_TRUE(users.empty());
}

// ---------- Full CRUD flow ----------
TEST_F(UserRepositoryTest, FullCrudFlow) {
    // Create
    EXPECT_TRUE(repo->insert(User(0, "Dave", "dave@mail.com", 40)));
    auto users = repo->getAll();
    ASSERT_EQ(users.size(), 1);
    int id = users[0].getId();

    // Read
    EXPECT_EQ(users[0].getName(), "Dave");

    // Update
    EXPECT_TRUE(repo->update(User(id, "David", "david@mail.com", 41)));
    users = repo->getAll();
    EXPECT_EQ(users[0].getName(), "David");
    EXPECT_EQ(users[0].getAge(), 41);

    // Delete
    EXPECT_TRUE(repo->remove(id));
    users = repo->getAll();
    EXPECT_TRUE(users.empty());
}
