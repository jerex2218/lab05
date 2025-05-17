#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Account.h"

class MockAccount : public Account {
public:
    MockAccount(int id = 0, int balance = 0) : Account(id, balance) {}
    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int diff), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
};

TEST(AccountTest, GetBalanceReturnsCorrectValue) {
    Account acc(1, 1000);
    ASSERT_EQ(acc.GetBalance(), 1000);
}

TEST(AccountTest, ChangeBalanceThrowsWhenUnlocked) {
    Account acc(1, 1000);
    ASSERT_THROW(acc.ChangeBalance(100), std::runtime_error);
}

TEST(AccountTest, ChangeBalanceWorksWhenLocked) {
    Account acc(1, 1000);
    acc.Lock();
    ASSERT_NO_THROW(acc.ChangeBalance(100));
    ASSERT_EQ(acc.GetBalance(), 1100);
}
TEST(AccountTest, LockUnlockSequence) {
    Account acc(1, 1000);
    acc.Lock();
    ASSERT_THROW(acc.Lock(), std::runtime_error);
    acc.Unlock();
    ASSERT_NO_THROW(acc.Lock());
}
