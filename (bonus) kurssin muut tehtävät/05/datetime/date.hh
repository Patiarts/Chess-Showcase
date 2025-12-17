#ifndef DATE_HH
#define DATE_HH

#include <string>

const int MIN_YEAR = 1000;
const int MAX_YEAR = 9999;
const int MONTH_LENGTHS[2][12] = {{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                                  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
const int MONTH_COUNT = 12;

class Date
{
public:
    Date(int year, int month, int day);
    virtual ~Date();

    int getYear() const;
    int getMonth() const;
    int getDay() const;

    bool isLeapYear() const;

    virtual std::string toString() const;
private:
    bool isLegal() const;

    int year_;
    int month_;
    int day_;
};

#endif // DATE_HH
