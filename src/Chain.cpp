#include "Chain.h"

#include <iostream>
#include "interface.h"

using namespace std;

void test_chain()
{
    cout << "==========simple chain==========" << endl;
    {
        Chain< int(int) > chain([](int i) { return i + 1; });
        auto result = chain.Then([](int i) { return i + 1; }).Then(
            [](int i) { return i + 1; }).Run(0);
        cout << "chain result: " << result.get() << endl;;
    }
}