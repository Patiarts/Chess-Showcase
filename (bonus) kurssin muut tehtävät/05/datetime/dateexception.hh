#ifndef DATEEXCEPTION_HH
#define DATEEXCEPTION_HH

#include <stdexcept>

class DateException : public std::domain_error
{
public:
    DateException(const char* message);
    virtual ~DateException();
};

#endif // DATEEXCEPTION_HH
