#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Transaction.h"
#include "Account.h"

class MockAccount : public Account {
public:
    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int diff), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
};

TEST(TransactionTest, MakeTransactionSuccess) {
    MockAccount from, to;
    Transaction tr;

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(from, GetBalance()).WillOnce(testing::Return(1000));
    EXPECT_CALL(to, GetBalance()).WillOnce(testing::Return(200));
    EXPECT_CALL(from, ChangeBalance(-300)).Times(1);
    EXPECT_CALL(to, ChangeBalance(300)).Times(1);
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    ASSERT_TRUE(tr.Make(from, to, 300));
}
