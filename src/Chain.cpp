#include "Chain.h"

#include "interface.h"

using namespace std;

void test_chain()
{
    cout << "==========simple chain==========" << endl;
    {
        Chain< int(int) > chain([](int i) { cout << "f1(int)->int" << endl; return i + 1; });
        auto result = chain.Then([](int i) { cout << "f2(int)->int" << endl; return i + 1; }).Then(
            [](int i) { cout << "f3(int)->int" << endl; return i + 1; }).Run(0);
        cout << "chain result: " << result.get() << endl;

        auto result2 = chain.Run(5);
        cout << "chain result2: " << result2.get() << endl;
    }

    cout << "==========void return==========" << endl;
    {
        Chain< void(void) > chain([]() { cout << "f1(void)->void" << endl; });
        auto result = chain.Then([]() { cout << "f2(void)->void" << endl; })
            .Then([]() { cout << "f3(void)->void" << endl; }).Run();
    }
}