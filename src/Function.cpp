#include "Function.h"

#include <functional>
#include <string>

#include "interface.h"

using namespace std;

namespace func {
void func1()
{
    cout << "func1()->void" << endl;
}

int func2(int i, string s)
{
    cout << "func2(int, string)->int" << endl;
    return (i + 1);
}

void func3(int i1, int i2, int i3, int i4)
{
    cout << i1 << " " << i2 << " " 
        << i3 << " " << i4 << endl;
    cout << "func3(int, int, int, int)->void" << endl;
}

void func4(const F& a)
{
    cout << "func4(F)->void" << endl;
}
}

void test_function()
{
    cout << "==========STL function==========" << endl;
    {
        function< void() > f1(func::func1);
        function< int(int, string) > f2(func::func2);

        f1();
        cout << f2(3, "functional") << endl;
    }

    cout << "==========bind==========" << endl;
    {
        function< void(int, int) > f3 = 
            bind(func::func3, placeholders::_2, 7, placeholders::_1, 8);
        function< void(int) > f4 =
            bind(func::func3, placeholders::_1, 10, placeholders::_1, placeholders::_1);
        
        f3(6, 9);
        f4(5);
    }

    cout << "==========lambda==========" << endl;
    {
        F f;
        function< void() > f5 = bind(func::func4, F());
        function< void() > f6 = bind(func::func4, f);
        function< void() > f7 = []() { func::func4(F()); };
        function< void() > f8 = [=]() { func::func4(f); };
        function< void() > f9 = [&]() { func::func4(f); };

        f5();
        f6();
        f7();
        f8();
        f9();
    }
}
