#ifndef NUM4_H
#define NUM4_H
#include <iostream>

using namespace std;

class A {
public:
    ~A() { cout << "A::~A()" << endl; }
    void f1() { cout << "A::f1()" << endl; }
    virtual void f2() { cout << "A::f2()" << endl; }
};
class B : public A {
public:
    virtual ~B() { cout << "B::~B()" << endl; }
    virtual void f1() { cout << "B::f1()" << endl; }
    void f2() { cout << "B::f2()" << endl; }
    virtual void f3() = 0;
};
class C : public B {
public:
    ~C() { cout << "C::~C()" << endl; }
    void f1() { cout << "C::f1()" << endl; }
    virtual void f3() { cout << "C::f3()" << endl; }
};
#endif

