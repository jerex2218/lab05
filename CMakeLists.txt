cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(banking)

option(BUILD_TESTS "Build tests" ON)
option(COVERAGE "Enable coverage reporting" ON)

include_directories(${PROJECT_SOURCE_DIR}/include)


add_library(banking STATIC
    src/Account.cpp
    src/Transaction.cpp
)

if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
    )
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    
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

    add_test(NAME banking_tests COMMAND banking_tests)
endif()
