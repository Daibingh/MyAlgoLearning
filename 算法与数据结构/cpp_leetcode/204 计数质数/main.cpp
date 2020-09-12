#include "utils.hpp"
using namespace std;


/*
统计所有小于非负整数 n 的质数的数量。

示例:

输入: 10
输出: 4
解释: 小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7 。
*/

// 常规方法 O(n^2) 超时
class Solution2 {
public:
    int countPrimes(int n) {
        int cnt = 0;
        for (int i=2;i<n;++i) {
            if (isPrime(i)) ++cnt;
        }
        return cnt;
    }

    bool isPrime(int n) {
        if (n==1) return false;
        for (int j=2;j<=sqrt(n);++j) {
            if (n%j==0) return false;
        }
        return true;
    }
};

// 用先找出来的质数的倍数排除合数, 注意遍历的边界【爱拉托逊斯筛法】
class Solution {
public:
    int countPrimes(int n) {
        vector<int> flag(n, 1);
        for (int i=2; i<sqrt(n); ++i) {
            if (flag[i]) {   
                for (int j=i*i; j<n; j+=i) {
                    flag[j] = false;
                }
            }
        }
        int cnt = 0;
        for (int i=2;i<n;++i) {
            if (flag[i]) ++cnt;
        }
        return cnt;
    }
};
