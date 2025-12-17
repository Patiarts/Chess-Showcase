#include "date.hh"
#include "dateexception.hh"

Date::Date(int year, int month, int day):
    year_(year), month_(month), day_(day)
{
    if (!isLegal()){
        std::string error_message = "Illegal date " + toString();
        throw DateException(error_message.c_str());
    }
}

Date::~Date() {}

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

bool Date::isLeapYear() const
{
    return year_%4 == 0 && (year_%100 != 0 || year_%400 == 0);
}

std::string Date::toString() const
{
    std::string year_string = std::to_string(year_);
    std::string month_string = ((month_ < 10)? "0" : "") + std::to_string(month_);
    std::string day_string = ((day_ < 10)? "0" : "") + std::to_string(day_);

    return day_string + '.' + month_string + '.' + year_string;

}

bool Date::isLegal() const
{
    bool legal_month = year_ >= 1 && month_ <= MONTH_COUNT;
    if (!legal_month){
        return false;
    }
    bool legal_year = year_ >= MIN_YEAR && year_ <= MAX_YEAR;
    bool legal_day = day_ >= 1 && day_ <= MONTH_LENGTHS[isLeapYear()][month_ -1];
    return legal_year && legal_day;
}


