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

class SD : public S
{
public:
    SD()
    {
        cnt = count++;
        std::cout << "SD() " << cnt << std::endl;
    }

    ~SD()
    {
        std::cout << "~SD() " << cnt << std::endl;
    }
};

size_t S::count = 0;

#endif // CXX_PRACTICE_SMART_POINTER_H
