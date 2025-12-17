#include "timedepositaccount.hh"
#include <iostream>

TimeDepositAccount::TimeDepositAccount(std::string owner):
    Account(owner), years_time_(0), days_left_(0)
{

}

TimeDepositAccount::~TimeDepositAccount() {}

bool TimeDepositAccount::take_money(double amount)
{
    if(days_left_ > 0){
        std::cout << "ERROR! Cannot take money: deposit time has not expired" << std::endl;
        return false;
    }
    return Account::take_money(amount);
}

void TimeDepositAccount::print() const
{
    Account::print();
    std::cout << "::: Days left : " << days_left_ << std::endl;
}

void TimeDepositAccount::set_times(int new_years)
{
    years_time_ = new_years;
    reset_time_days();
}

void TimeDepositAccount::reset_time_days()
{
    days_left_ = 365 * years_time_;
}

void TimeDepositAccount::spend_time(int days)
{
    days_left_ -= days;
}

int TimeDepositAccount::get_days() const
{
    return days_left_;
}
