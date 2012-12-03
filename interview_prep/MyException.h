#ifndef MYEXCEPTION_H
#define MYEXCEPTOIN_H
#include <exception>

using namespace std;

class MyException: public exception
{
    private:
    string _message;

    public:
    MyException()
    {
    }
     
    ~MyException() throw(){}

    MyException(string message)
    {
        _message = message;
    }
    const char * what() const throw()
    {
        return _message.c_str();
    }
};

#endif
