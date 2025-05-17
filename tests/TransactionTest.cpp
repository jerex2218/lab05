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
    
    int id() const override { return id_; }
    void setId(int id) { id_ = id; }  /
    
private:
    int id_ = 0;
};

TEST(TransactionTest, MakeTransactionSuccess) {
    MockAccount from, to;
    from.setId(1);
    to.setId(2);
    Transaction tr;

    // Ожидаемые вызовы в правильном порядке:
    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, ChangeBalance(300)).Times(1);
    EXPECT_CALL(from, GetBalance()).WillOnce(testing::Return(1000));
    EXPECT_CALL(from, ChangeBalance(-301)).Times(1);
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    ASSERT_TRUE(tr.Make(from, to, 300));
}
