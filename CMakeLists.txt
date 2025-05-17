cmake_minimum_required(VERSION 3.10...3.27)

project(banking LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(COVERAGE "Enable coverage reporting" ON)

# Основные исходные файлы (без папок include/src)
set(BANKING_SOURCES
    Account.cpp
    Transaction.cpp
)

# Основная библиотека
add_library(banking STATIC ${BANKING_SOURCES})

if(BUILD_TESTS)
    # Загрузка GoogleTest
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE  # Убираем предупреждение
    )
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    # Тестовые файлы
    set(TEST_SOURCES
        AccountTest.cpp
        TransactionTest.cpp
    )

    # Исполняемый файл для тестов
    add_executable(banking_tests ${TEST_SOURCES})
    target_link_libraries(banking_tests banking GTest::GTest GTest::Main)

    if(COVERAGE)
        target_compile_options(banking_tests PRIVATE --coverage)
        target_link_libraries(banking_tests --coverage)
    endif()

    add_test(NAME banking_tests COMMAND banking_tests)
endif()
