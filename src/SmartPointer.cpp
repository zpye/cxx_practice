#include "SmartPointer.h"

#include <memory>
#include "interface.h"

using namespace std;

void test_smartpointer()
{
    cout << "==========simple shared pointer==========" << endl;
    {
        shared_ptr< S > s1(new S());
        shared_ptr< S > s2 = make_shared< S >();

        {
            shared_ptr< S > s3(s1);
        }

        {
            shared_ptr< S > s3 = s1;
        }

        {
            shared_ptr< S > s3 = make_shared< S >();
            s3.reset(new S());
        }

        {
            shared_ptr< S > s4 = move(s2);
        }

        cout << "simple shared pointer end" << endl;
    }

    cout << "==========unique pointer==========" << endl;
    {
        unique_ptr< S > u1(new S());
        // unique_ptr< S > u2 = u1;
        unique_ptr< S > u2 = move(u1);
        unique_ptr< S > u3(move(u2));

        cout << "unique pointer end" << endl;
    }
}
