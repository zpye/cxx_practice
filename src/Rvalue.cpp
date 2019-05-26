#include "Rvalue.h"

#include "interface.h"

using namespace std;

namespace rvalue {
A func1() {
  A a;
  a.setn(15);
  return a;
}

A func2(A a) {
  A b = a;
  A c = move(a);
  return move(b);
}

A&& func3() {
  A a;
  return move(a);
}

A&& func4() {
  A&& a = A();
  a.setn(15);
  return move(a);
}

A func5() {
  A&& a = A();
  A b = a;
  A&& c = A();
  return c;
}

A func6(A&& a) {
  A b = a;
  return b;
}
}  // namespace rvalue

void test_rvalue() {
  cout << "==========class constructor==========" << endl;
  {
    rvalue::A a;
    rvalue::A a1(a);
    rvalue::A a2 = a;
    rvalue::A a3 = rvalue::A();

    rvalue::A b(10);
    a1 = b;
    a2 = rvalue::A(10);
    a3 = move(b);

    rvalue::A c(20);
    rvalue::A c1(move(c));
    rvalue::A c2 = move(c1);

    rvalue::A d;
    d = move(d);

    rvalue::A e;
    move(e);
  }

  cout << "==========return value==========" << endl;
  {
    rvalue::func1();
    rvalue::A a1 = rvalue::func1();
    rvalue::A a2 = rvalue::func2(rvalue::A());
    rvalue::A&& a3 = rvalue::func3();
    a3.setn(10);
    rvalue::A&& a4 = rvalue::func4();
    rvalue::A a5 = rvalue::func5();
    a5 = rvalue::func5();
    rvalue::A a6 = rvalue::func6(rvalue::A());
  }
}
