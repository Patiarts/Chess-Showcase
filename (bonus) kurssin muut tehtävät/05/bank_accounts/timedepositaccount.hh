#ifndef TIMEDEPOSITACCOUNT_HH
#define TIMEDEPOSITACCOUNT_HH

#include "account.hh"
#include <string>

class TimeDepositAccount : public Account
{
public:
    TimeDepositAccount(std::string owner);
    virtual ~TimeDepositAccount();

    virtual bool take_money(double amount);

    virtual void print() const;

    void set_times(int new_years);
    void reset_time_days();
    void spend_time(int days);

    int get_days() const;
private:
    int years_time_;
    int days_left_;
};

#endif // TIMEDEPOSITACCOUNT_HH
