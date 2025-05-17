#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Account.h"
#include "Transaction.h"

class MockAccount : public Account {
public:
    MockAccount(int id, int balance) : Account(id, balance) {}
    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int diff), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
};

TEST(TransactionTest, TransferBetweenDifferentAccounts) {
    MockAccount from(1, 2000);
    MockAccount to(2, 500);
    Transaction tr;

    // Правильная последовательность вызовов
    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, ChangeBalance(300)).Times(1);
    EXPECT_CALL(from, GetBalance()).WillOnce(Return(2000));
    EXPECT_CALL(from, ChangeBalance(-301)).Times(1);
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    ASSERT_TRUE(tr.Make(from, to, 300));
}
