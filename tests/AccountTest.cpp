#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Account.h"

class MockAccount : public Account {
public:
    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int diff), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
};

TEST(AccountTest, GetBalance) {
    MockAccount acc;
    EXPECT_CALL(acc, GetBalance()).WillOnce(testing::Return(100));
    ASSERT_EQ(acc.GetBalance(), 100);
}

TEST(AccountTest, LockUnlock) {
    Account acc(123, 500);
    acc.Lock();
    ASSERT_NO_THROW(acc.ChangeBalance(100));
    acc.Unlock();
    ASSERT_THROW(acc.ChangeBalance(100), std::runtime_error);
}
