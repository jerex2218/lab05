#include <gtest/gtest.h>
#include "Account.h"

TEST(AccountTest, GetBalanceReturnsInitialValue) {
    Account acc(1, 1000);
    ASSERT_EQ(acc.GetBalance(), 1000);
}

TEST(AccountTest, ChangeBalanceRequiresLock) {
    Account acc(1, 1000);
    ASSERT_THROW(acc.ChangeBalance(100), std::runtime_error);
    acc.Lock();
    ASSERT_NO_THROW(acc.ChangeBalance(100));
    ASSERT_EQ(acc.GetBalance(), 1100);
}

TEST(AccountTest, ChangeBalanceRequiresLock) {
    Account acc(1, 1000);
    ASSERT_EQ(acc.GetBalance(), 1100);
}
