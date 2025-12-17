#include "datetime.hh"
#include "dateexception.hh"

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second):
    Date(year, month, day), hour_(hour), minute_(minute), second_(second)
{
    if (!isLegalTime()){
        std::string error_string = "Illegal time " + toStringTime();
        throw DateException(error_string.c_str());
    }
}

DateTime::~DateTime() {}

int DateTime::getHour() const
{
    return hour_;
}

int DateTime::getMinute() const
{
    return minute_;
}

int DateTime::getSecond() const
{
    return second_;
}

std::string DateTime::toString() const
{
    return Date::toString() + ' ' + toStringTime();
}

bool DateTime::isLegalTime() const
{
    bool legal_hour = hour_ >= 0 && hour_ <= MAX_HOUR;
    bool legal_minute = minute_ >= 0 && minute_ <= MAX_MIN_SEC;
    bool legal_second = second_ >= 0 && second_ <= MAX_MIN_SEC;

    return legal_hour && legal_minute && legal_second;
}

std::string DateTime::toStringTime() const
{
    std::string hour_string = ((hour_ < 10)? "0" : "") + std::to_string(hour_);
    std::string minute_string = ((minute_ < 10)? "0" : "") + std::to_string(minute_);
    std::string second_string = ((second_ < 10)? "0" : "") + std::to_string(second_);

    return hour_string + ':' + minute_string + ':' + second_string;
}
