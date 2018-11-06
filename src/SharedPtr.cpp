#include "SharedPtr.h"

#include <iostream>
#include "interface.h"

using namespace std;

class TestB
{
public:
    TestB()
    {
        cnt = count++;
        std::cout << "TestB() " << cnt << std::endl;
    }

    ~TestB()
    {
        std::cout << "~TestB() " << cnt << std::endl;
    }

protected:
    static size_t count;
    size_t cnt;
};

class TestD : public TestB
{
public:
    TestD()
    {
        cnt = count++;
        std::cout << "TestD() " << cnt << std::endl;
    }

    ~TestD()
    {
        std::cout << "~TestD() " << cnt << std::endl;
    }
};

size_t TestB::count = 0;

void test_sharedptr()
{
    cout << "==========simple SharedPtr==========" << endl;
    {
        SharedPtr< TestB > sp1(new TestB());
        SharedPtr< TestB > sp2(sp1);
        SharedPtr< TestB > sp3(move(sp1));

        SharedPtr< int > sp4(new int(0));
        SharedPtr< int[] > sp5(new int[10]{1});
        SharedPtr< TestB[] > sp6(new TestB[5]);
    }
}