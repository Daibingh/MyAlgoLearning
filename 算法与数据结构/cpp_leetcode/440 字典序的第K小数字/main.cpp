#include <bits/stdc++.h>

using namespace std;

/*
给定整数 n 和 k，找到 1 到 n 中字典序第 k 小的数字。
注意：1 ≤ k ≤ n ≤ 10^9。

*/

typedef long long ll;

class Solution {
public:
    int findKthNumber(int n, int k) {
        int i = 1;
        int pre = 1;
        while (i<k) {
            int cnt = get_count(pre, n);
            if (i+cnt>k) {  // 超了，缩小范围
                pre *= 10;
                ++i;
            }
            else {  // 没超，继续增大 pre
                ++pre;
                i += cnt;
            }
        }
        return pre;
    }

    // 计算以 pre 为前缀的数字 (<=n) 的个数
    int get_count(int pre, ll n) {
        ll a = pre, b = pre+1;
        int cnt = 0;
        for (;a<=n; a*=10,b*=10) {
            cnt += min(b, n+1) - a;
        }
        return cnt;
    }
};