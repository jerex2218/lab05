TEST(TransactionTest, MakeTransactionSuccess) {
    MockAccount from(1, 2000);
    MockAccount to(2, 500);
    Transaction tr;

    testing::Sequence s1, s2;
    
    EXPECT_CALL(from, Lock()).InSequence(s1);
    EXPECT_CALL(to, Lock()).InSequence(s2);
    EXPECT_CALL(to, ChangeBalance(300)).InSequence(s2);
    EXPECT_CALL(from, GetBalance()).InSequence(s1).WillOnce(Return(2000));
    EXPECT_CALL(from, ChangeBalance(-301)).InSequence(s1);
    EXPECT_CALL(from, Unlock()).InSequence(s1);
    EXPECT_CALL(to, Unlock()).InSequence(s2);

    ASSERT_TRUE(tr.Make(from, to, 300));
}

TEST(TransactionTest, RollbackOnFailedDebit) {
    MockAccount from(1, 300);
    MockAccount to(2, 0);
    Transaction tr;

    EXPECT_CALL(from, GetBalance()).WillOnce(Return(300));
    EXPECT_CALL(to, ChangeBalance(200)).Times(1);
    EXPECT_CALL(to, ChangeBalance(-200)).Times(1); // Rollback
    
    ASSERT_FALSE(tr.Make(from, to, 200));
}
