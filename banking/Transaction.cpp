bool Transaction::Make(Account& from, Account& to, int sum) {
    if (from.id() == to.id()) 
        throw std::logic_error("invalid action");
    if (sum < 0) 
        throw std::invalid_argument("sum can't be negative");
    if (sum < 100) 
        throw std::logic_error("too small");
    if (fee_ * 2 > sum) 
        return false;

    Guard guard_from(from);
    Guard guard_to(to);

    bool success = Debit(from, sum + fee_);
    if (success) {
        Credit(to, sum);
    }

    SaveToDataBase(from, to, sum);
    return success;
}
