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
        cout << "sizeof void*: " << sizeof(void*) << endl;
    }

    cout << "==========function and class==========" << endl;
    {
        cout << "sizeof function: " << sizeof(&EmptyFunction) << endl;
        cout << "sizeof empty class: " << sizeof(Empty) << endl;
        cout << "sizeof class with char: " << sizeof(Variable< char >) << endl;
        cout << "sizeof class with int: " << sizeof(Variable< int >) << endl;
        cout << "sizeof class with double: " << sizeof(Variable< double >) << endl;
        cout << "sizeof class with void*: " << sizeof(Variable< void* >) << endl;
        cout << "sizeof class with float*: " << sizeof(Variable< float* >) << endl;
        cout << "sizeof class with function: " << sizeof(Function) << endl;
        cout << "sizeof class with static function: " << sizeof(StaticFunction) << endl;
        cout << "sizeof class with virtual function: " << sizeof(VirtualFunction) << endl;
    }
}