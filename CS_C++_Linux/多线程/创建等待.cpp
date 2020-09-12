#include <bits/stdc++.h>
#include <thread>
#include <unistd.h>
#include <pthread.h>

using namespace std;

/*
程序的用意：
- 创建、join/detach 线程
- thread() 传参
- 传参过程变量拷贝次数
- unique_ptr 传参
- 硬件并发数：std::thread::hardware_concurrency()
*/

class A {
public:
    A() {
        cout<<"new"<<endl;
    }
    A(const A& a) {cout<<"copy, id="<<this_thread::get_id()<<endl;}
};


void func(const string& str) {
    cout<<std::this_thread::get_id()<<", "<<str<<endl;
}

void func2(string str) {
    sleep(2);
    fstream out("CS_C++_Linux/多线程/out.txt", fstream::out);
    out<<str<<endl;
    out.close();
}

void func3(const A& a) {
    cout<<"线程5："<<this_thread::get_id()<<endl;
}

void func4(const unique_ptr<int>& p) {}


int main() {

    cout<<"Total concurrency number: "<<std::thread::hardware_concurrency()<<endl;

    cout<<"主线程："<<this_thread::get_id()<<endl;

    thread th1(func, "thread1 created!");
    thread th2(func, "thread2 created!");
    thread th3(func2, "thread3 created!");
    std::function<void(string)> f = [](string str) {cout<<str<<endl;};
    thread th4(f, "hhhh");

    A a;
    thread th5(func3, a);

    unique_ptr<int> p(new int);
    thread th6(func4, move(p));

    if (th1.joinable())
        th1.join();
    th2.join();
    th3.detach();
    th4.join();
    th5.join();
    th6.join();
    // return 0;
    pthread_exit(0); // 退出线程而不退出进程，C++ 没有替代品！？
}