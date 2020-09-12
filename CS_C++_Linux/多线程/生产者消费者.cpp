#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <bits/stdc++.h>

using namespace std;


/*
条件变量的作用：让某个线程可以根据某个条件休眠，同时，改条件可以被另外一个线程改变，例如：
produce 表示 生产者的等待条件 (q.size()<max_size) 

cond.wait(lck) block and unlock lck, until notified. Once notified lock lck and return.

while (!cond) cv.wait(lck) 等价于 cv.wait(lck, cond)

持有锁 -> 条件成立 -> 往下走 -> ...
持有锁 -> 条件不成立 -> 放弃锁，休眠 -> 唤醒
  ^\_________________________________|
*/

std::mutex mtx;
std::condition_variable produce,consume;
queue<int> q;
int max_size = 20;

void consumer () {
    while (q.size()<max_size) {
        std::unique_lock<std::mutex> lck(mtx);
        std::this_thread::sleep_for(std::chrono::milliseconds(rand()%500));
        consume.wait(lck, [&](){ return q.size()!=0;} );  // 持有锁并判断等待条件是否成立，如果成立，继续往下；否则，放弃锁，进入休眠
        auto t = q.front();                               // 当另一个线程 对改条件变量调用 notify_one() 函数时，醒来先持有锁并...
        q.pop();
        produce.notify_one();
    }
}

void producer (int id) {
    while (q.size()<max_size) {
        std::unique_lock<std::mutex> lck(mtx);
        std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200));
        produce.wait(lck, [&](){return q.size()<max_size;});  // 等价于 while (q.size()==max_size) produce.wait(lck);
        q.push(id);
        cout<<q.size()<<endl;
        consume.notify_one();
    }
}

int main ()
{
  std::thread consumers[2],producers[2];  // 两个生产者，两个消费者
  for (int i=0; i<2; ++i) {
    consumers[i] = std::thread(consumer);
    producers[i] = std::thread(producer,i+1);
  }

  // join them back:
  for (int i=0; i<2; ++i) {
    producers[i].join();
    consumers[i].join();
  }

  return 0;
}