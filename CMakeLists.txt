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
    # Загрузка GoogleTest через FetchContent (используем существующий тег)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0  # Используем существующий тег
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    
    # Отключаем ненужные компоненты
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(googletest)

    # Подключаем тесты
    add_executable(banking_tests
        tests/AccountTest.cpp
        tests/TransactionTest.cpp
    )
    
    target_include_directories(banking_tests PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/banking
    )
    
    # Подключаем зависимости
    target_link_libraries(banking_tests
        banking
        GTest::gtest
        GTest::gmock
        GTest::gtest_main
    )
    
    include(GoogleTest)
    gtest_discover_tests(banking_tests)
endif()
