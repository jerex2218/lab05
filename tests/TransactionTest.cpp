TEST(TransactionTest, TransferBetweenDifferentAccounts) {
    MockAccount from(1, 2000); // Начальный баланс достаточен для 300 + 1 (комиссия)
    MockAccount to(2, 500);
    Transaction tr;

    testing::InSequence seq;

    // Ожидаемые вызовы в правильном порядке
    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    
    // Проверка баланса и списание с отправителя
    EXPECT_CALL(from, GetBalance()).WillOnce(Return(2000));
    EXPECT_CALL(from, ChangeBalance(-301)).Times(1); // 300 + 1
    
    // Зачисление получателю
    EXPECT_CALL(to, ChangeBalance(300)).Times(1);
    
    // Разблокировка
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    ASSERT_TRUE(tr.Make(from, to, 300));
}
