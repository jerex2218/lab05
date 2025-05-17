# Загрузка GoogleTest и GMock через FetchContent
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.13.0  # Стабильная версия
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(tests
    AccountTest.cpp
    TransactionTest.cpp
)

target_link_libraries(tests PRIVATE
    banking
    GTest::gtest_main
    GMock::gmock
)

include(GoogleTest)
gtest_discover_tests(tests)

# Покрытие кода
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(tests PRIVATE --coverage)
    target_link_libraries(tests PRIVATE --coverage)
endif()
