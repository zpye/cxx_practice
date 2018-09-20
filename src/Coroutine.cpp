/**
 * refer to "Protothreads"(http://dunkels.com/adam/pt/index.html) 
 * and its c++ implement(https://github.com/benhoyt/protothreads-cpp)
*/

#include "Coroutine.h"

#include <iostream>
#include "interface.h"

using namespace std;

class ProtoB;

class ProtoA : public Protothreads
{
public:
    bool Run() override;

    void setB(ProtoB* _ptB)
    {
        ptB = _ptB;
    }

private:
    ProtoB* ptB;
    size_t i;
};

class ProtoB : public Protothreads
{
public:
    bool Run() override;

    void setA(ProtoA* _ptA)
    {
        ptA = _ptA;
    }

private:
    ProtoA* ptA;
    size_t i;
};

bool ProtoA::Run()
{
    PT_BEGIN();

    for(i = 0; i < 5; ++i)
    {
        cout << "ProtoA i: " << i << endl;
        PT_WAIT_THREAD(*ptB);
    }

    PT_END();
}

bool ProtoB::Run()
{
    PT_BEGIN();

    for(i = 0; i < 10; ++i)
    {
        cout << "ProtoB i: " << i << endl;
        PT_WAIT_THREAD(*ptA);
    }

    PT_END();
}

void test_coroutine()
{
    cout << "==========coroutine==========" << endl;
    {
        ProtoA ptA;
        ProtoB ptB;

        ptA.setB(&ptB);
        ptB.setA(&ptA);

        ptB.Run();
    }
}