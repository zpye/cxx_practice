#ifndef CXX_PRACTICE_FUNCTION_H
#define CXX_PRACTICE_FUNCTION_H

#include <iostream>

class F
{
public:
    F()
    {
        c = count++;
        std::cout << "F() " << c << std::endl;
    }

    ~F()
    {
        std::cout << "~F() " << c << std::endl;
    }

    F(const F& a)
    {
        c = count++;
        std::cout << "F(const F&) " << c << std::endl;
    }

    F(F&& a)
    {
        c = count++;
        std::cout << "F(F&&) " << c << std::endl;
    }

protected:
    static size_t count;
    size_t c;
};

size_t F::count = 0;

#endif // CXX_PRACTICE_FUNCTION_H