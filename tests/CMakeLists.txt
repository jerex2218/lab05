find_package(GTest REQUIRED)

add_executable(banking_tests
    AccountTest.cpp
    TransactionTest.cpp
)
target_link_libraries(banking_tests banking GTest::GTest)

