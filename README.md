# SQLite CRUD (OOP) – C++ Project

Clean folder structure with Google Test unit tests.

## Folder Structure

```
sqlite_crud_oop/
├── CMakeLists.txt
├── include/                  # Header files (.h)
│   ├── User.h
│   ├── Database.h
│   ├── UserRepository.h
│   └── Menu.h
├── src/                      # Source files (.cpp)
│   ├── main.cpp
│   ├── User.cpp
│   ├── Database.cpp
│   ├── UserRepository.cpp
│   └── Menu.cpp
├── lib/                      # Third-party (SQLite amalgamation)
│   ├── sqlite3.h             ← place here
│   └── sqlite3.c             ← place here
├── tests/                    # Unit tests
│   ├── test_user.cpp
│   └── test_user_repository.cpp
└── reports/                  # For future test/report output
```

## Setup

1. Put `sqlite3.c` and `sqlite3.h` inside the **lib/** folder.
2. Open the project in VS Code.
3. CMake: Configure → CMake: Build

## Build & Run

```bash
# Configure (from project root)
cmake -B build -G "MinGW Makefiles"     # Windows MinGW
# or
cmake -B build                          # Linux / macOS

# Build
cmake --build build

# Run application
./build/sqlite_crud          # Linux/macOS
.\build\sqlite_crud.exe      # Windows

# Run unit tests
./build/unit_tests           # Linux/macOS
.\build\unit_tests.exe       # Windows

# Or with CTest
cd build && ctest --output-on-failure
```

## Notes

- Tests use an in-memory database (`:memory:`) – they never touch `users.db`.
- First configure downloads Google Test automatically (needs internet once).
