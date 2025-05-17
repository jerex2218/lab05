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
    # Загрузка GoogleTest
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.13.0
    )
    FetchContent_MakeAvailable(googletest)

    # Исполняемый файл тестов
    add_executable(tests
        tests/AccountTest.cpp
        tests/TransactionTest.cpp
    )
    
    # Подключение зависимостей (используем только gtest_main)
    target_link_libraries(tests PRIVATE
        banking
        GTest::gtest_main
        GTest::gmock
    )
    
    # Настройки покрытия кода
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(tests PRIVATE --coverage)
        target_link_options(tests PRIVATE --coverage)
    endif()

    # Добавление тестов в CTest
    include(GoogleTest)
    gtest_discover_tests(tests)
endif()
