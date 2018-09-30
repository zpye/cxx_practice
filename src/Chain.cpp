#include "Chain.h"

#include "interface.h"

using namespace std;

void test_chain()
{
    cout << "==========simple chain==========" << endl;
    {
        Chain< int(int) > chain([](int i) { cout << "f1" << endl; return i + 1; });
        auto result = chain.Then([](int i) { cout << "f2" << endl; return i + 1; }).Then(
            [](int i) { cout << "f3" << endl; return i + 1; }).Run(0);
        cout << "chain result: " << result.get() << endl;;
    }
}