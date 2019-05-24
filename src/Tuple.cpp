#include "Tuple.h"

#include <iostream>
#include <map>
#include <tuple>
#include <string>
#include <functional>

#include "interface.h"

using namespace std;

void test_tuple()
{
    cout << "==========basic tuple==========" << endl;
    {
        tuple< char, int, double, string > tp1('t', 1, 0.2, "tuple");
        tuple< float, T > tp2 = make_tuple(1.5f, T());

        int i = get< 1 >(tp1);
        string s = get< 3 >(tp1);
        T a = get< 1 >(tp2);
        cout << i << " " << s << " " << a.l << endl;
    }

    cout << "==========tie==========" << endl;
    {
        char c = 'c';
        int i = 1;
        float f = 2.5f;

        tuple< char&, int&, float& > tp1 = tie(c, i, f);
        c = 'd';
        get< 1 >(tp1) = 2;
        cout << get<0>(tp1) << " " << get< 1 >(tp1) << endl;
        cout << &f << " " << &get< 2 >(tp1) << endl;

        double d;
        string s;

        tuple< double, string, long > tp2(1.2345, "tie", 1000);
        tie(d, s, ignore) = tp2;
        cout << d << " " << s << endl;
    }

    cout << "==========forward_as_tuple==========" << endl;
    {
        map< int, string > m;
        m.emplace(piecewise_construct,
                  forward_as_tuple(10),
                  forward_as_tuple(20, 'a'));
        cout << "m[10] = " << m[10] << endl;
    }
}