#ifndef CXX_PRACTICE_CLASS_H
#define CXX_PRACTICE_CLASS_H

#include <iostream>

class Base
{
public:
    Base() : i(0)
    {
        cnt = count++;
        std::cout << "Base() " << cnt << std::endl;
    }

    virtual ~Base()
    {
        std::cout << "~Base() " << cnt << std::endl;
    }

    void func1()
    {
        std::cout << "Base func1 " << cnt << std::endl;
    }

    void func2()
    {
        i = 0;
        std::cout << "Base func2 " << cnt << std::endl;
    }

    virtual void func3()
    {
        std::cout << "Base func3 " << cnt << std::endl;
    }

    static void func4()
    {
        std::cout << "Base func4 static " << count << std::endl;
    }

private:
    char c;
    int i;
    double d;
    long double* ld;
    static float f;

protected:
    static size_t count;
    size_t cnt;
};

class Derived : public Base
{
public:
    Derived() : i(1)
    {
        std::cout << "Derived() " << cnt << std::endl;
    }

    virtual ~Derived()
    {
        std::cout << "~Derived() " << cnt << std::endl;
    }

    void func1()
    {
        std::cout << "Derived func1" << std::endl;
    }

    virtual void func3() override
    {
        std::cout << "Derived func3 " << cnt << std::endl;
    }

    static void func4()
    {
        std::cout << "Derived func4 static " << count << std::endl;
    }

private:
    int i;
};

size_t Base::count = 0;

#endif // CXX_PRACTICE_CLASS_H