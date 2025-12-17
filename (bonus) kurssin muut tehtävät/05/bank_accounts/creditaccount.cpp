#include "creditaccount.hh"
#include <iostream>

CreditAccount::CreditAccount(const std::string& owner):
    Account(owner), credit_limit_(0)
{}

CreditAccount::~CreditAccount() {}

bool CreditAccount::take_money(double amount)
{
    if (get_balance() + credit_limit_ < amount){
        std::cout << "ERROR! Cannot take money: credit limit overflow" << std::endl;
        return false;
    }
    set_balance(get_balance() - amount);
    return true;
}

void CreditAccount::print() const
{
    Account::print();
    std::cout << "::: Credit limit : " << credit_limit_ << std::endl;
}

void CreditAccount::set_credit_limit(double limit)
{
    credit_limit_ = limit;
}

double CreditAccount::get_credit_limit() const
{
    return credit_limit_;
}
