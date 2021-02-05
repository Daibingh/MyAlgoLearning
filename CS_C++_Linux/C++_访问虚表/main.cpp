#include <bits/stdc++.h>

using namespace std;

class A {

public:
    virtual void f() { cout<<"hhhh"<<endl; }
};

typedef void(*Fun)(void);

int main() {
    A a, b;
   auto f = (Fun) *((long*) *(long*)(&a)); 
   auto g = (Fun) *((long*) *(long*)(&b)); 
   f();
   g();

   cout<<"虚表地址: "<< *(long*)(&a) <<endl;
   cout<<"虚表地址: "<< *(long*)(&b) <<endl;

   cout<<"虚表中第一个函数的地址: "<< *(long*)*(long*)(&a) <<endl;
   cout<<"虚表中第一个函数的地址: "<< *(long*)*(long*)(&b) <<endl;
}