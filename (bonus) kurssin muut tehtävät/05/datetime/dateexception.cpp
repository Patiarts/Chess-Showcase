#include "dateexception.hh"





DateException::DateException(const char *message): std::domain_error(message)
{

}

DateException::~DateException() {}
