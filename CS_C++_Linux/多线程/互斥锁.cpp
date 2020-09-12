// #include <bits/stdc++.h>
// #include <thread>
// #include <unistd.h>
// #include <pthread.h>

// using namespace std;


// /*
// - 测试各种锁
// */

// int cnt = 0;

// void fun1(int n) {
//     for (;n;--n) {
//         cnt = cnt * 2;
//         cnt = cnt - 2;
//     }
// }

// void fun2(int n) {
//     for (;n;--n) {
//         cnt = cnt + 2;
//         cnt = cnt / 2 ;
//     }
// }

// int main() {
//     thread t1 = thread(fun1, 100);
//     thread t2 = thread(fun2, 100);

//     t1.join();
//     t2.join();
//     cout<<cnt<<endl;
// }