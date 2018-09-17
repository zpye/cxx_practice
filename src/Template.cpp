#include "Template.h"

#include "interface.h"

using namespace std;

template< typename F, typename T >
auto template_func(F f, T t)
    ->decltype(f(t))
{
    return f(t);
}

void test_template()
{
    cout << "==========template function==========" << endl;
    {
        TempFunc< int >();
        TempFunc< float >();
        TempFunc< char >();

        TempFunc< int >();
        TempFunc< float >();
        TempFunc< char >();
    }

    cout << "==========template class==========" << endl;
    {
        TempClass< char, char > tc1;
        TempClass< double, int > tc2;
        TempClass< float, int > tc3;
        TempClass< long, char > tc4;
        TempClass< unsigned int, int > tc5;
        TempClass< float, int > tc6;
    }

    cout << "==========enable_if==========" << endl;
    {
        TempFunc2();
        TempFunc2< long, 3 >();
        TempFunc2< int, 8 >();

        cout << "value: " << TempStruct<>::value << endl;
        cout << "value: " << TempStruct< 0 >::value << endl;
        cout << "value: " << TempStruct< 4 >::value << endl;
        cout << "value: " << TempStruct< 10 >::value << endl;
    }

    cout << "==========auto==========" << endl;
    {
        auto i1 = 1; // int
        auto i2 = 5 + 6; //int
        auto* i3 = &i1; // int *
        auto& i4 = i2; // int &
        const auto& i5 = 10; // const int &

        auto i6 = i3; // int *
        auto i7 = i4; // int
        auto i8 = i5; // int

        cout << "template_func: " 
            << template_func([](double t) { return 3 * t; }, 1.2);
    }
}