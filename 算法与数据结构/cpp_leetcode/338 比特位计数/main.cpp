#include "utils.hpp"

using namespace std;

/*
给定一个非负整数 num。对于 0 ≤ i ≤ num 范围中的每个数字 i ，计算其二进制数中的 1 的数目并将它们作为数组返回。
*/


class Solution2 {
public:
    vector<int> countBits(int num) {
        vector<int> res;
        for (int i=0;i<=num;++i) {
            res.push_back(helper(i));
        }
        return res;
    }
    // 巧用 位运算， x & (x-1) 将 最后一个 1 置零
    int helper(int x) {
        int cnt =0 ;
        for (;x!=0;++cnt) {
            x &= x-1;
        }
        return cnt;
    }
};

// 动态规划
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> res(num+1,0);
        for (int i=1;i<=num;++i) {
            res[i] = res[i&(i-1)]+1;
        }
        return res;
    }
};