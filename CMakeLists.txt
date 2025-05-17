cmake_minimum_required(VERSION 3.14)
project(lab05 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная библиотека
add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)
target_include_directories(banking PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/banking
)

# Тесты
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    # Загрузка GoogleTest через FetchContent
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0  # Используем конкретную версию
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    # Исполняемый файл тестов
    add_executable(tests
        tests/AccountTest.cpp
        tests/TransactionTest.cpp
    )
    
    # Подключение зависимостей
    target_link_libraries(tests PRIVATE
        banking
        GTest::gtest_main
        GMock::gmock_main
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
