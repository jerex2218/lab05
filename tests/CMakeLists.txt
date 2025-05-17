# Альтернативный способ подключения GoogleTest
find_package(GTest REQUIRED)
find_package(GMock REQUIRED)

add_executable(tests
    AccountTest.cpp
    TransactionTest.cpp
)

target_link_libraries(tests PRIVATE
    banking
    GTest::GTest
    GMock::GMock
    GTest::Main
)

include(GoogleTest)
gtest_discover_tests(tests)

# Установка покрытия
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(tests PRIVATE --coverage)
    target_link_options(tests PRIVATE --coverage)
endif()
