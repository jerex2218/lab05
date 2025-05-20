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
    if (fee_ * 2 > sum) return false; // Теперь это условие сработает раньше
    if (sum < 100) throw std::logic_error("too small");
}

    {
        Guard guard_from(from);  // Блокируем from первым
        Guard guard_to(to);      // Блокируем to вторым

        if (!Debit(from, sum + fee_)) {
            return false;
        }
        Credit(to, sum);
    }  // Разблокировка происходит автоматически в обратном порядке

    SaveToDataBase(from, to, sum);
    return true;
}

void Transaction::Credit(Account& account, int sum) {
    account.ChangeBalance(sum);
}

bool Transaction::Debit(Account& account, int sum) {
    if (account.GetBalance() >= sum) {
        account.ChangeBalance(-sum);
        return true;
    }
    return false;
}

void Transaction::SaveToDataBase(Account& from, Account& to, int sum) {
   
}
