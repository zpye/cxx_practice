#include "Singleton.h"

#include <iostream>

#include "interface.h"

using namespace std;

class A : public Singleton< A >
{
private: 
    friend class Singleton< A >;
    A(int i = 0)
    {
        cout << "constructor A(int i), i = " << i << endl;
    }
};

class B
{
public:
    B()
    {
        cout << "constructor B()" << endl;
    }
};

class C : public SingletonNoArg< C >
{
private:
    friend class SingletonNoArg< C >;
    C()
    {
        cout << "constructor C()" << endl;
    }
};

void test_Singleton()
{
    A* inst1 = A::GetInstance(1);
    A* inst2 = A::GetInstance();
    A* inst3 = A::GetInstance(2);

    B* inst4 = Singleton< B >::GetInstance();
    B* inst5 = Singleton< B >::GetInstance();

    C* inst6 = C::GetInstance();
    C* inst7 = C::GetInstance();
}