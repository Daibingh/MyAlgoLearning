#include "utils.hpp"
using namespace std;

/*
编写一个算法来判断一个数 n 是不是快乐数。

「快乐数」定义为：对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和，然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。如果 可以变为  1，那么这个数就是快乐数。

如果 n 是快乐数就返回 True ；不是，则返回 False 。
*/


class Solution {
    unordered_set<int> mem;
public:
    bool isHappy(int n) {
        if (n==1) return true;
        if (mem.count(n)) return false;
        mem.insert(n);
        return isHappy(helper(n));
    }

    int helper(int n ) {
        int ret = 0;
        while (n) {
            int t = n%10;
            ret += t*t;
            n/=10;
        }
        // cout<<ret<<endl;
        return ret;
    }
};