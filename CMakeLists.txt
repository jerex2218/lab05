cmake_minimum_required(VERSION 3.14)
project(lab05 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем библиотеку banking
add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)
target_include_directories(banking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/banking)

# Тесты
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
    )
    FetchContent_MakeAvailable(googletest)

    add_executable(tests
        tests/AccountTest.cpp
        tests/TransactionTest.cpp
    )
    
    # Единый стиль target_link_libraries с ключевыми словами
    target_link_libraries(tests PRIVATE
        banking
        GTest::GTest
        GTest::GMock
    )
    
    # Покрытие кода
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(tests PRIVATE --coverage)
        target_link_options(tests PRIVATE --coverage)
    endif()

    include(GoogleTest)
    gtest_discover_tests(tests)
endif()
