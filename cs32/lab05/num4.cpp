#include "num4.h"

void f1() {
    C c1;
    A a1 = c1;
    a1.f1();
    a1.f2();
}

void f2() {
    B* b1 = new C();
    b1->f1();
    b1->f2();
    b1->f3();
    delete b1;
}

int main(){
	f1();
	cout<<endl;
	f2();
	cout<<endl;
}