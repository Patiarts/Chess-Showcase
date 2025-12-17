#include "account.hh"
#include <iostream>

// Initialize the static attribute running_number_
int Account::running_number_ = 0;

Account::Account(const std::string& owner):
    holder_(owner), iban_(""), balance_(0)
{
    generate_iban();
}

Account::~Account() {}

void Account::save_money(double amount)
{
    balance_ += (amount >= 0)? amount : -amount;
}

bool Account::take_money(double amount)
{
    if(amount > balance_){
        return false;
    }
    balance_ -= amount;
    return true;
}

bool Account::transfer_to(Account *other_account, double amount)
{
    if(other_account == this){
        return false;
    }
    if(!take_money(amount)){
        return false;
    }
    other_account->save_money(amount);
    return true;
}

void Account::print() const
{
    std::cout << holder_ << " : "
              << iban_ << " : "
              << balance_ << " euros" << std::endl;
}

void Account::print_iban() const
{
    std::cout << iban_;
}

double Account::get_balance() const
{
    return balance_;
}

void Account::set_balance(const double to)
{
    balance_ = to;
}

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}
