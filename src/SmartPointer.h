#ifndef CXX_PRACTICE_SMART_POINTER_H
#define CXX_PRACTICE_SMART_POINTER_H

#include <iostream>

class S
{
public:
    S()
    {
        cnt = count++;
        std::cout << "S() " << cnt << std::endl;
    }

    ~S()
    {
        std::cout << "~S() " << cnt << std::endl;
    }

protected:
    static size_t count;
    size_t cnt;
};

size_t S::count = 0;

#endif // CXX_PRACTICE_SMART_POINTER_H