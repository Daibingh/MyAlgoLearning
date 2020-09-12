#include <bits/stdc++.h>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>

using namespace std;

// - https://github.com/caitaozhan/ThreadPool

// 凡是，多个线程 读写 的变量，就要考虑 加锁 或采用 原子变量


class ThreadPool {

    mutex mtx;
    condition_variable cond;
    vector<thread> threads;
    queue<std::function<void()>> que;
    std::atomic<bool> closed;

public:
    ThreadPool(int num_worker):closed(false) {
        
        threads.resize(num_worker);
        for (int i=0;i<num_worker;++i) {
            threads[i] = thread(&ThreadPool::run, this);
        }
    }

    ~ThreadPool() {
        close();
        join();
        
    }

    void run() {

        for (;;) {
            function<void()> task;
            {
                std::unique_lock<mutex> lck(mtx);
                while (!closed && que.empty()) cond.wait(lck);
                if (closed && que.empty()) 
                    return;    // 线程池关闭代表不会再有任务加入，只有 关闭了 且 任务队列为空 才退出
                task = que.front();
                que.pop();
            }
            task();
        }

    }

    void close() {
        closed = true;  
        cond.notify_all();  // 条件发生改变，唤醒与此条件有关的线程
    }

    template<typename FunctionType>
    void submit(FunctionType f)
    {
        std::unique_lock<mutex> lck(mtx);
        que.push(std::function<void()>(f));
        cond.notify_one();
    }

    void join() {
        for (auto & t : threads) {
            if (t.joinable()) t.join();
        }
    }
};


void fun() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
}


int main() {
    auto t1=std::chrono::steady_clock::now();
    ThreadPool pool(8);
    for (int i=0;i<8;++i) {
        pool.submit(fun);
        // fun();
    }
    pool.close();
    pool.join();
    auto t2=std::chrono::steady_clock::now();
    double dr_s = std::chrono::duration<double>(t2-t1).count();
    cout <<  "花费了"<< dr_s<< "秒" << endl;
}
