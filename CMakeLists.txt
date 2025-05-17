cmake_minimum_required(VERSION 3.10)
project(lab05)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная библиотека из папки banking
add_library(banking STATIC
    banking/Account.cpp
    banking/Transaction.cpp
)

# Указываем, где искать заголовочные файлы
target_include_directories(banking PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/banking
)

# Тесты (если они есть)
if(EXISTS "tests/AccountTest.cpp")
    find_package(GTest REQUIRED)
    
    add_executable(banking_tests
        tests/AccountTest.cpp
        tests/TransactionTest.cpp
    )
    
    target_link_libraries(banking_tests
        banking
        GTest::GTest
        GTest::Main
    )
    
    add_test(NAME banking_tests COMMAND banking_tests)
endif()
