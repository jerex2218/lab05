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
};

TEST(TransactionTest, MakeTransactionSuccess) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    Transaction tr;

    // Последовательность вызовов согласно Transaction.cpp:
    // 1. Lock обоих аккаунтов
    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    
    // 2. Credit получателю (положительное изменение)
    EXPECT_CALL(to, ChangeBalance(300)).Times(1);
    
    // 3. Проверка баланса и дебет отправителя
    EXPECT_CALL(from, GetBalance()).WillOnce(testing::Return(1000));
    EXPECT_CALL(from, ChangeBalance(-301)).Times(1); // сумма + комиссия
    
    // 4. Unlock обоих аккаунтов
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    ASSERT_TRUE(tr.Make(from, to, 300));
}

TEST(TransactionTest, SameAccountFailure) {
    MockAccount acc(1, 1000);
    Transaction tr;
    EXPECT_THROW(tr.Make(acc, acc, 100), std::logic_error);
}

TEST(TransactionTest, SmallAmountFailure) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    Transaction tr;
    EXPECT_THROW(tr.Make(from, to, 50), std::logic_error);
}

TEST(TransactionTest, InsufficientFunds) {
    MockAccount from(1, 300);
    MockAccount to(2, 0);
    Transaction tr;

    EXPECT_CALL(from, GetBalance()).WillOnce(testing::Return(300));
    EXPECT_FALSE(tr.Make(from, to, 200)); // 200 + 1(fee) > 300
}
