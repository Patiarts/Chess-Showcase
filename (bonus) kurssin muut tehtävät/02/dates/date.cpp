// COMP.CS.115 - 4.6.1 päivämäärät - date.cpp
// Author: Patrik Reitkivi
// st.num: 151106280

#include "date.hh"

Date::Date(int year, int month, int day):
    year_(year), month_(month), day_(day) {}

Date::~Date(){}

int Date::getYear() const
{
    return year_;
}

int Date::getMonth() const
{
    return month_;
}

int Date::getDay() const
{
    return day_;
}

std::string Date::toString() const
{
    std::string d = std::to_string(day_);
    std::string m = std::to_string(month_);
    std::string y = std::to_string(year_);
    return d + "." +m + "." + y;
}

std::string Date::toIsoFormat() const
{
    std::string d = std::to_string(day_);
    std::string m = std::to_string(month_);
    std::string y = std::to_string(year_);

    if (d.length() == 1){
        d = "0" + d;
    }
    if(m.length() == 1){
        m = "0" + m;
    }

    return y + "-" + m + "-" + d;
}

bool Date::operator<(const Date &other) const
{
    int yother = other.getYear();
    if (year_ != yother){return year_ < yother;}

    int mother = other.getMonth();
    if (month_ != mother){return month_ < mother;}

    int dother = other.getYear();
    return day_ < dother;
}

bool Date::operator==(const Date &other) const
{
    int yother = other.getYear();
    int mother = other.getMonth();
    int dother = other.getYear();

    return year_==yother && month_==mother && day_== dother;
}

bool Date::isLeapYear() const
{
    return (year_ % 4 == 0) and ((year_ % 100 != 0) or (year_ % 400 == 0));
}

bool Date::isLegal() const
{
    bool legayear = abs(year_ - FIRST_YEAR) + abs(LAST_YEAR - year_) == LAST_YEAR - FIRST_YEAR;
    bool legamonth = abs(month_- 1) + abs(12 - month_) == 12 - 1;
    bool legaday = (legamonth)? abs(day_- 1) + abs(MONTH_SIZES[isLeapYear()][month_-1] - day_) == MONTH_SIZES[isLeapYear()][month_-1] - 1 : false; // :D

    // bool valiyear =  FIRST_YEAR  <= year_  && year_  <= LAST_YEAR;
    // bool valimonth = FIRST_MONTH <= month_ && month_ <= 12;
    // bool validay =   FIRST_DAY   <= day_   && day_   <= MONTH_SIZES[isLeapYear()][month_-1];

    // std::cout << (legayear == valiyear) << ", " << (legamonth == valimonth) << ", " << (legaday == validay);
    return legayear && legamonth && legaday;
}

