#include "LazyEvaluation.h"

#include <iostream>
#include "interface.h"

using namespace std;

void test_lazy_evaluation()
{
    cout << "==========lazy evaluation: add two vectors==========" << endl;
    {
        float a[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        float b[5] = {7.0f, 8.0f, 9.0f, 10.0f, 11.0f};
        float c[5] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

        Vec va(a, 5), vb(b, 5), vc(c, 5);
        vc = va + vb;
        cout << "vc = va + vb" << endl;
        
        for(size_t i = 0; i < 5; ++i)
        {
            cout << "va[" << i << "] = " << a[i] << ", ";
            cout << "vb[" << i << "] = " << b[i] << ", ";
            cout << "vc[" << i << "] = " << c[i] << endl;
        }
    }
}