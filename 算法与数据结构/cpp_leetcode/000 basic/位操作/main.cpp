#include "utils.hpp"

using namespace std;

int main() {
    
    // 和空格做 异或 大小写 切换
    cout<<(char)('a' ^ ' ')<<endl;
    cout<<(char)('Z' ^ ' ')<<endl;

    // 判断两个数是否异号，异或小于零=>异号
    cout<< ( ( 1 ^ -5) < 0 ) <<endl;
    cout<< ( ( -1 ^ -5) < 0 ) <<endl;

    // 消除数字 n 的⼆进制表⽰中的最后⼀个 1
    int n = rand() % 100;
    cout<< ( n & (n-1) ) <<endl;

    // 取出最后一个 “1” lowbit
    cout<< ( n & (-n) ) <<endl;

    return 0;
}