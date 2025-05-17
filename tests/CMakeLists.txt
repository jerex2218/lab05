include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
)
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
