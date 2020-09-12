#include <bits/stdc++.h>
#include <thread>
#include <unistd.h>
#include <pthread.h>
#include <future>

using namespace std;

/*
- std::async() 与 thread() 不同之一是，前者必须执行完，进程才退出，后者必须有 join 才行
*/

int func1() {
    sleep(5);
    cout<<this_thread::get_id()<<endl;
    return 0;
}

int main() {
    cout<<this_thread::get_id()<<endl;
    auto res = std::async(func1);
    // cout<<res.get()<<endl;
}