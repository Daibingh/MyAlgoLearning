#include <bits/stdc++.h>
using namespace std;

/*
编写一个程序判断给定的数是否为丑数。

丑数就是只包含质因数 2, 3, 5 的正整数。

示例 1:

输入: 6
输出: true
解释: 6 = 2 × 3
*/

// 记忆搜索
class Solution {
    unordered_map<int, bool> mem;
public:
    bool isUgly(int num) {
        if (num==0) return false;
        if (num==1) return true;
        if (mem.count(num)) return mem[num];
        bool ret =  num%2==0 && isUgly(num/2) 
                    || num%3==0 && isUgly(num/3) 
                    || num%5==0 && isUgly(num/5) ;
        return mem[num]=ret;
    }
};