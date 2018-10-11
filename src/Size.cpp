#include "Size.h"

#include <iostream>
#include "interface.h"

using namespace std;

void test_size()
{
    cout << "==========basic type==========" << endl;
    {
        cout << "sizeof bool: " << sizeof(bool) << endl;
        cout << "sizeof char: " << sizeof(char) << endl;
        cout << "sizeof short: " << sizeof(short) << endl;
        cout << "sizeof int: " << sizeof(int) << endl;
        cout << "sizeof long: " << sizeof(long) << endl;
        cout << "sizeof long long: " << sizeof(long long) << endl;
        cout << "sizeof float: " << sizeof(float) << endl;
        cout << "sizeof double: " << sizeof(double) << endl;
        cout << "sizeof long double: " << sizeof(long double) << endl;
    }
}