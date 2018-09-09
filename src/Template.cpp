#include "Template.h"

#include "interface.h"

using namespace std;

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
}