#include "Rvalue.h"

#include "interface.h"

using namespace std;

namespace rvalue {
    A func1()
    {
        A a;
        a.setn(15);
        return a;
    }

    A func2(A a)
    {
        A b = a;
        A c = move(a);
        return move(b);
    }

    A&& func3()
    {
        A a;
        return move(a);
    }

    A&& func4()
    {
        A&& a = A();
        a.setn(15);
        return move(a);
    }

    A func5()
    {
        A&& a = A();
        A b = a;
        A&& c = A();
        return c;
    }

    A func6(A&& a)
    {
        A b = a;
        return b;
    }
}

void test_rvalue()
{
    cout << "==========class constructor==========" << endl;
    {
        A a;
        A a1(a);
        A a2 = a;
        A a3 = A();

        A b(10);
        a1 = b;
        a2 = A(10);
        a3 = move(b);

        A c(20);
        A c1(move(c));
        A c2 = move(c1);

        A d;
        d = move(d);

        A e;
        move(e);
    }

    cout << "==========return value==========" << endl;
    {
        rvalue::func1();
        A a1 = rvalue::func1();
        A a2 = rvalue::func2(A());
        A&& a3 = rvalue::func3();
        a3.setn(10);
        A&& a4 = rvalue::func4();
        A a5 = rvalue::func5();
        a5 = rvalue::func5();
        A a6 = rvalue::func6(A());
    }
}
