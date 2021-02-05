#include <bits/stdc++.h>

using namespace std;

////////////////////////////////////////////////////
// 实现 Share_ptr
template <typename T>
class Share_ptr {
public:
    Share_ptr():cnt(new int(0)), p(nullptr) {}
    Share_ptr(T * t): cnt(new int(1)), p(t) {}
    ~Share_ptr() {
        if (--*cnt==0) {
            delete p;
            delete cnt;
        }
    }

    Share_ptr(Share_ptr& sp):cnt(&(++*sp.cnt)),p(sp.p) {}

    Share_ptr& operator=(Share_ptr& sp) {
        ++*sp.cnt;  // 先加, 防止自我赋值出错
        if (--*cnt==0) {
            delete p;
            delete cnt;
        }
        cnt = sp.cnt;
        p = sp.p;
        return *this;
    }

    int count() const {
        return *cnt;
    }

    T* operator->() {
        return p;
    }

    T& operator*() {
        return *p;
    }

private:
    int * cnt;
    T * p;

};


struct Point {
    int x,y;
    Point(int x, int y):x(x),y(y) {}
};

int main() {
    Share_ptr<Point> p;
    cout<<p.count()<<endl;
    Share_ptr<Point> p2(new Point(100, 200));
    cout<<p2->x<<endl;
    cout<<p2.count()<<endl;
    p = p2;
    cout<<p.count()<<endl;
    cout<<p2.count()<<endl;
}