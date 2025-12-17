// COMP.CS.115 - 4.6.1 päivämäärät - dateperiod.hh
// Author: Patrik Reitkivi
// st.num: 151106280

#ifndef DATEPERIOD_HH
#define DATEPERIOD_HH

#include "date.hh"

class DatePeriod
{
public:
    DatePeriod(const Date& d1, const Date& d2);
    virtual ~DatePeriod();

    std::string getStart();
    std::string getEnd();
    unsigned int getDiff();
private:
    int get_tested();
    Date date1_;
    Date date2_;

};

#endif // DATEPERIOD_HH
