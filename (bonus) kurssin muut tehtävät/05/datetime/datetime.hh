#ifndef DATETIME_HH
#define DATETIME_HH

#include "date.hh"

const int MAX_HOUR = 23;
const int MAX_MIN_SEC = 59;


class DateTime : public Date
{
public:
    DateTime(int year, int month, int day, int hour, int minute, int second);
    virtual ~DateTime();

    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    virtual std::string toString() const;
private:
    bool isLegalTime() const;
    std::string toStringTime() const;

    int hour_;
    int minute_;
    int second_;
};

#endif // DATETIME_HH
