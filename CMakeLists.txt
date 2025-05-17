cmake_minimum_required(VERSION 3.10...3.27)  # Обновлённая версия
project(lab05 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная библиотека
add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)

# Тесты
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    # Загрузка GoogleTest и GoogleMock
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE  # Фикс предупреждения
    )
    FetchContent_MakeAvailable(googletest)

    # Подключаем тесты
    add_executable(banking_tests
        tests/AccountTest.cpp
        tests/TransactionTest.cpp
    )
    
    # Подключаем зависимости
    target_link_libraries(banking_tests
        banking
        GTest::GTest
        GTest::GMock
        GTest::GMockMain
    )
    
    # Автоматическое обнаружение тестов
    include(GoogleTest)
    gtest_discover_tests(banking_tests)
endif()
