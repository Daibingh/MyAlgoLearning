#include "bits/stdc++.h"

using namespace std;

class A {
public:
    void f() {
        cout<<"A::f()"<<endl;
    }
    void g() {
        cout<<"A::g()"<<endl;
    }
};

class B: public A {
public:
    void f() {
        cout<<"B::f()"<<endl;
    }
    void h() {
        cout<<"B::h()"<<endl;
    }
};


int main() {

    // 没有虚函数，对象 往上转型
    { 
        A a;
        B b;
        b.f();
        A a2 = static_cast<A>(b);
        // A a2 = dynamic_cast<A>(b); // error: cannot dynamic_cast ‘b’ (of type ‘class B’) to type ‘class A’ (target is not pointer or reference)
        a2.f();
    }


    // 没有虚函数，指针 往上转型
    {
        A* a = new A;
        B* b = new B;
        b->f();
        // A* a2 = static_cast<A*>(b);
        A* a2 = dynamic_cast<A*>(b);
        a2->f();
    }


    // 父类指针指向指针对象，向下转型
    {
        A* a = new A;
        A* a2 = new B;

        a2->f();
        B* b = static_cast<B*>(a2);
        // B* b = dynamic_cast<B*>(a2);  // A 必须有虚函数，否则不成功
        b->f();
    }
    
}