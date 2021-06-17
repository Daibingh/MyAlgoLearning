#include "utils.hpp"
#include <thread>

using namespace std;


/*
一种方法使用静态指针，延迟创建对象，要注意线程安全问题, 对象创建和析构
另一种方法使用局部静态对象
https://blog.csdn.net/q5707802/article/details/79251148

*/


class Singleton {

private:
    static Singleton* ptr;
    static std::mutex mtx;

protected:

    Singleton(string str) {
        this->str = str;
    }

public:
    string str;

    static Singleton* getInstance(string str) {
        if (!ptr)
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (!ptr) {
                ptr = new Singleton(str);
            }
        }
        return ptr;
    }

    Singleton(Singleton& s) = delete;

    Singleton& operator=(Singleton& s) = delete;
    
};

Singleton* Singleton::ptr = nullptr;  // 静态成员初始化在 类外部，重写一边定义
std::mutex Singleton::mtx;

int main() {
    auto ptr = Singleton::getInstance("111");
    cout<<ptr->str<<endl;
    auto ptr2 = Singleton::getInstance("222");
    cout<<ptr2->str<<endl;
    assert (ptr==ptr2);
}