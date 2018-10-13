#ifndef CXX_PRACTICE_SIZE_H
#define CXX_PRACTICE_SIZE_H

// function
void EmptyFunction()
{
}

// empty class
class Empty
{};

// class with variable
template< typename T >
class Variable
{
    T var;
};

// class with pointer
template< typename T >
class Pointer
{
    T* ptr;
};

// class with function
class Function
{
    void func1()
    {
    }

    void func2()
    {
    }
};

// class with static function
class StaticFunction
{
    static void func1()
    {

    }

    static void func2()
    {

    }
};

// class with virtual function
class VirtualFunction
{
    virtual void func1()
    {

    }

    virtual void func2()
    {

    }
};

#endif // CXX_PRACTICE_SIZE_H