#ifndef CXX_PRACTICE_RVALUE_H
#define CXX_PRACTICE_RVALUE_H

#include <iostream>

class A
{
public:
    A(int _n = 5) : n(_n)
    {
        c = count++;
        p = new uint8_t[n];
        for(size_t i = 0; i < n; ++i)
        {
            *(p + i) = static_cast< uint8_t >(i);
        }
        std::cout << "A() " << c << std::endl;
    }

    ~A()
    {
        delete[] p;
        std::cout << "~A() " << c << std::endl;
    }

    A(const A& _A)
    {
        c = count++;
        if(this != &_A)
        {
            n = _A.n;
            p = new uint8_t[n];
            for(size_t i = 0; i < n; ++i)
            {
                *(p + i) = *(_A.p + i);
            }
            std::cout << "A(const A&) " << c << std::endl;
        }
    }

    A& operator =(const A& _A)
    {
        if(this != &_A)
        {
            n = _A.n;
            p = new uint8_t[n];
            for(size_t i = 0; i < n; ++i)
            {
                *(p + i) = *(_A.p + i);
            }
            std::cout << "A& operator =(const A&) " << c << std::endl;
        }

        return (*this);
    }

    A(A&& _A)
    {
        c = count++;
        if(this != &_A)
        {
            n = _A.n;
            p = _A.p;
            _A.p = nullptr;
            std::cout << "A(A&&) " << c << std::endl;
        }
    }

    A& operator =(A&& _A)
    {
        if(this != &_A)
        {
            n = _A.n;
            p = _A.p;
            _A.p = nullptr;
            std::cout << "A& operator =(A&&) " << c << std::endl;
        }

        return (*this);
    }

    void setn(size_t _n)
    {
        n = _n;
    }

private:
    size_t n;
    uint8_t* p;

protected:
    static size_t count;
    size_t c;
};

size_t A::count = 0;

#endif // CXX_PRACTICE_RVALUE_H