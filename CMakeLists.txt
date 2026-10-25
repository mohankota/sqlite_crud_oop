cmake_minimum_required(VERSION 3.14)
project(SQLiteCRUD)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------------------------------
# Paths
# -------------------------------------------------------
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR     ${CMAKE_SOURCE_DIR}/src)
set(LIB_DIR     ${CMAKE_SOURCE_DIR}/lib)
set(TEST_DIR    ${CMAKE_SOURCE_DIR}/tests)

# -------------------------------------------------------
# Main application
# -------------------------------------------------------
add_executable(sqlite_crud
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/User.cpp
    ${SRC_DIR}/Database.cpp
    ${SRC_DIR}/UserRepository.cpp
    ${SRC_DIR}/Menu.cpp
    ${LIB_DIR}/sqlite3.c
)

target_include_directories(sqlite_crud PRIVATE
    ${INCLUDE_DIR}
    ${LIB_DIR}
)

if(WIN32)
    target_compile_options(sqlite_crud PRIVATE
        $<$<COMPILE_LANGUAGE:C>:-Wno-unused-parameter>
    )
else()
    target_link_libraries(sqlite_crud PRIVATE pthread dl)
endif()

# -------------------------------------------------------
# Google Test
# -------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# -------------------------------------------------------
# Unit tests
# -------------------------------------------------------
add_executable(unit_tests
    ${TEST_DIR}/test_user.cpp
    ${TEST_DIR}/test_user_repository.cpp
    ${SRC_DIR}/User.cpp
    ${SRC_DIR}/Database.cpp
    ${SRC_DIR}/UserRepository.cpp
    ${LIB_DIR}/sqlite3.c
)

target_include_directories(unit_tests PRIVATE
    ${INCLUDE_DIR}
    ${LIB_DIR}
)

target_link_libraries(unit_tests PRIVATE GTest::gtest_main)

if(WIN32)
    target_compile_options(unit_tests PRIVATE
        $<$<COMPILE_LANGUAGE:C>:-Wno-unused-parameter>
    )
else()
    target_link_libraries(unit_tests PRIVATE pthread dl)
endif()

include(GoogleTest)
gtest_discover_tests(unit_tests)
