cmake_minimum_required(VERSION 3.14)
project(lab05 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная библиотека
add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)
target_include_directories(banking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/banking)

# Тесты
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    # Загрузка GoogleTest через FetchContent
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.14.0
    )
    FetchContent_MakeAvailable(googletest)

    # Подключаем тесты
    add_executable(banking_tests
        tests/AccountTest.cpp
        tests/TransactionTest.cpp
    )
    
    # Настройка включения заголовков
    target_include_directories(banking_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/banking)
    
    # Подключаем зависимости
    target_link_libraries(banking_tests
        banking
        GTest::gtest_main
        GMock::gmock_main
    )
    
    # Включение GoogleTest
    include(GoogleTest)
    gtest_discover_tests(banking_tests)
endif()
