#include "Class.h"

#include "interface.h"

using namespace std;

void test_class()
{
    // construct and deconstruct
    cout << "==========construct and deconstruct==========" << endl;
    {
        Base b;
        Derived d;

        Base* bp = new Base();
        Derived* dp = new Derived();

        delete bp;
        delete dp;
    }

    // sizeof
    cout << "==========sizeof==========" << endl;
    {
        cout << "size of Base: " << sizeof(Base) << endl;
        cout << "size of Derived: " << sizeof(Derived) << endl;
    }

    // functions
    cout << "==========functions===========" << endl;
    {
        Base b;
        Derived d;

        b.func1();
        b.func2();
        b.func3();
        b.func4();

        Base::func4();

        d.func1();
        d.Base::func1();
        d.func2();
        d.func3();
        d.func4();
        
        Derived::func4();
        Derived::Base::func4();
    }

    // dynamic binding
    cout << "==========dynamic binding==========" << endl;
    {
        Base* bp = new Base();
        Derived* dp = new Derived();

        Base* bp2 = dp;
        bp2->func1();
        bp2->func2();
        bp2->func3();

        Base* bp3 = new Derived();
        bp3->func1();
        bp3->func2();
        bp3->func3();

        Derived* dp2 = static_cast< Derived* >(bp2);
        dp2->func1();
        dp2->func2();
        dp2->func3();

        dp2 = static_cast< Derived* >(bp);
        dp2->func1();
        dp2->func2();
        dp2->func3();

        Derived* dp3 = dynamic_cast< Derived* >(bp2);
        dp3->func1();
        dp3->func2();
        dp3->func3();

        dp3 = dynamic_cast< Derived* >(bp);
        dp3->func1();
        // dp2->func2();
        // dp2->func3();

        Derived* dp4 = static_cast< Derived* >(nullptr);
        dp4->func1();
        // dp4->func2();
        // dp4->func3();

        // dp4 = dynamic_cast< Derived* >(nullptr);

        delete bp;
        delete dp;
        delete bp3;
    }
}