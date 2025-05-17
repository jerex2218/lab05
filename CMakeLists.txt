cmake_minimum_required(VERSION 3.14)
project(lab05)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная библиотека
add_library(banking STATIC
    banking/Account.cpp
    banking/Transaction.cpp
)

target_include_directories(banking PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/banking
)

option(BUILD_TESTS "Build tests" ON)
option(COVERAGE "Enable coverage" ON)

if(BUILD_TESTS)
    # Новый надежный способ загрузки GTest
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(googletest)

    # Тесты
    add_executable(banking_tests
        tests/AccountTest.cpp
        tests/TransactionTest.cpp
    )

    target_link_libraries(banking_tests
        banking
        GTest::GTest
        GTest::Main
    )

    if(COVERAGE)
        target_compile_options(banking_tests PRIVATE --coverage)
        target_link_libraries(banking_tests --coverage)
    endif()

    enable_testing()
    add_test(NAME banking_tests COMMAND banking_tests)
endif()
