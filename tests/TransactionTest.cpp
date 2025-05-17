#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Transaction.h"
#include "Account.h"

class MockAccount : public Account {
public:
    MockAccount(int id = 0, int balance = 0) : Account(id, balance) {}
    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int diff), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
    int id() const override { return id_; }  // Реальная реализация
};

TEST(TransactionTest, MakeFailsWhenSameAccount) {
    MockAccount acc(1, 1000);
    Transaction tr;
    ASSERT_THROW(tr.Make(acc, acc, 100), std::logic_error);
}

TEST(TransactionTest, MakeSuccessWithSufficientFunds) {
    MockAccount from(1, 1500);
    MockAccount to(2, 500);
    Transaction tr;

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, ChangeBalance(300)).Times(1);
    EXPECT_CALL(from, GetBalance()).WillOnce(testing::Return(1500));
    EXPECT_CALL(from, ChangeBalance(-301)).Times(1);
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    ASSERT_TRUE(tr.Make(from, to, 300));
}
