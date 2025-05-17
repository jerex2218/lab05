cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lab05)

# Основная библиотека (из папки banking)
add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)

# Тесты (собираются, если включена опция BUILD_TESTS)
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    # Загрузка GoogleTest
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
    )
    FetchContent_MakeAvailable(googletest)

    # Подключаем тесты из папки tests/
    add_executable(banking_tests
        tests/AccountTest.cpp
        tests/TransactionTest.cpp
    )
    target_link_libraries(banking_tests banking gtest_main)

    # Автоматическое обнаружение тестов
    include(GoogleTest)
    gtest_discover_tests(banking_tests)
endif()
