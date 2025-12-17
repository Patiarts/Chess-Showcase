// COMP.CS.115 - 4.6.1 päivämäärät - dateperiod.cpp
// Author: Patrik Reitkivi
// st.num: 151106280


#include "dateperiod.hh"


DatePeriod::DatePeriod(const Date &d1, const Date &d2):
    date1_(d1), date2_(d2)
{
    if (date2_ < date1_){
        Date tmp = date1_;
        date1_ = date2_;
        date2_ = tmp;
    }
}

DatePeriod::~DatePeriod()
{}

std::string DatePeriod::getStart()
{
    return date1_.toIsoFormat();
}

std::string DatePeriod::getEnd()
{
    return date2_.toIsoFormat();
}

unsigned int DatePeriod::getDiff()
{
    const int POSITIVE = 1;
    const int NEGATIVE = -1;

    int lesser_year = date1_.getYear();
    int bigger_year = date2_.getYear();
    int small_month = date1_.getMonth();
    int great_month = date2_.getMonth();
    int smaller_day = date1_.getDay();
    int greater_day = date2_.getDay();

    int direction_to_sum_years_in = POSITIVE;
    int month_summation_direction = POSITIVE;

    bool leapy_first_date = date1_.isLeapYear() && Date(date1_.getYear(), 2, 28) < date1_;
    bool leapy_second_date = date2_.isLeapYear() && Date(date2_.getYear(), 2, 28) < date2_;

    if (lesser_year > bigger_year){
        std::swap(lesser_year, bigger_year);
        direction_to_sum_years_in = NEGATIVE;
    }
    if (small_month > great_month){
        std::swap(small_month, great_month);
        month_summation_direction = NEGATIVE;
    }

    int total_difference = 0;
    int sum_term = 0;

    for(int i = lesser_year; i < bigger_year; i++){
        sum_term = 365;
        sum_term += int((i % 4 == 0) && ((i % 100 != 0) || (i % 400 == 0)));
        sum_term *= direction_to_sum_years_in;
        total_difference += sum_term;
    }

    for(int i = small_month; i < great_month; i++){
        sum_term = MONTH_SIZES[0][i-1];
        sum_term *= month_summation_direction;
        total_difference += sum_term;
    }
    if(leapy_first_date){
        total_difference -= 1;
    }
    if(leapy_second_date){
        total_difference += 1;
    }

    total_difference += greater_day - smaller_day;

    return get_tested(); // :( ?
}

int DatePeriod::get_tested()
{
    // Tätä koodia (ei metodia) käytettiin vaan "oikean" erotuslaskurin debuggauksessa.
    // halusin vähentää for-looppien kestoa ja määrää: se oli vaikeaa.
    int years_difference = 0;
    int months_difference = 0;
    int days_difference = 0;
    int raw_total = 0;

    for(int i = FIRST_YEAR; i < date1_.getYear(); i++){
        years_difference -= 365 + int((i % 4 == 0) && ((i % 100 != 0) || (i % 400 == 0)));
    }
    for(int i = FIRST_YEAR; i < date2_.getYear(); i++){
        years_difference += 365 + int((i % 4 == 0) && ((i % 100 != 0) || (i % 400 == 0)));
    }

    for(int i = FIRST_MONTH; i < date1_.getMonth(); i++){
        months_difference -= MONTH_SIZES[date1_.isLeapYear()][i-1];
    }
    for(int i = FIRST_MONTH; i < date2_.getMonth(); i++){
        months_difference += MONTH_SIZES[date2_.isLeapYear()][i-1];
    }

    days_difference = date2_.getDay() - date1_.getDay();

    raw_total = years_difference + months_difference + days_difference;

    return raw_total;
}


