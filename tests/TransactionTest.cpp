#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Transaction.h"
#include "Account.h"

class MockAccount : public Account {
public:
    MockAccount() : Account(0, 0) {}
    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int diff), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
    MOCK_METHOD(int, id, (), (const, override)); 
};

TEST(TransactionTest, MakeTransactionSuccess) {
    MockAccount from, to;
    Transaction tr;

    // Устанавливаем разные ID
    ON_CALL(from, id()).WillByDefault(testing::Return(1));
    ON_CALL(to, id()).WillByDefault(testing::Return(2));

    // Ожидаемые вызовы в правильном порядке:
    // 1. Lock обоих аккаунтов
    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    
    // 2. Кредит получателю
    EXPECT_CALL(to, ChangeBalance(300)).Times(1);
    
    // 3. Дебет отправителя (с комиссией)
    EXPECT_CALL(from, GetBalance()).WillOnce(testing::Return(1000));
    EXPECT_CALL(from, ChangeBalance(-301)).Times(1);
    
    // 4. Unlock обоих аккаунтов
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    ASSERT_TRUE(tr.Make(from, to, 300));
}
