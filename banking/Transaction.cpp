#include "Transaction.h"
#include "Account.h"  // Добавлено
#include <cassert>
#include <iostream>
#include <stdexcept>

namespace {
struct Guard {
    Guard(Account& account) : account_(&account) { account_->Lock(); }
    ~Guard() { account_->Unlock(); }
private:
    Account* account_;
};
}  // namespace

Transaction::Transaction() : fee_(1) {}
Transaction::~Transaction() = default;

bool Transaction::Make(Account& from, Account& to, int sum) {
    if (from.id() == to.id()) throw std::logic_error("invalid action");
    if (sum < 0) throw std::invalid_argument("sum can't be negative");
    if (sum < 100) throw std::logic_error("too small");
    if (fee_ * 2 > sum) return false;

    Guard guard_from(from);
    Guard guard_to(to);

    if (!Debit(from, sum + fee_)) return false;
    Credit(to, sum);

    SaveToDataBase(from, to, sum);
    return true;
}

// Остальные методы остаются без изменений
