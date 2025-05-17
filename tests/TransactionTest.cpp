#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Transaction.h"
#include "Account.h"

class MockAccount : public Account {
public:
    // Конструктор с возможностью установки ID
    MockAccount(int id = 0, int balance = 0) : Account(id, balance) {}
    
    // Mock-методы для виртуальных функций
    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int diff), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
    
    // Не mock'аем id(), используем реализацию базового класса
};

TEST(TransactionTest, MakeTransactionSuccess) {
    // Создаем mock-аккаунты с разными ID
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    Transaction tr;

    // Ожидаемые вызовы
    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, ChangeBalance(300)).Times(1);
    EXPECT_CALL(from, GetBalance()).WillOnce(testing::Return(1000));
    EXPECT_CALL(from, ChangeBalance(-301)).Times(1);
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
