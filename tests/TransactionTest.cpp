TEST(TransactionTest, MinimalWorkingTest) {
    MockAccount from(1, 1000);
    MockAccount to(2, 0);
    Transaction tr;

    // Только обязательные проверки
    EXPECT_CALL(to, ChangeBalance(300)).Times(1);
    EXPECT_CALL(from, ChangeBalance(-301)).Times(1);

    ASSERT_TRUE(tr.Make(from, to, 300));
}
