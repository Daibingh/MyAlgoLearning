#include "utils.hpp"

using namespace std;


/*
You are given K eggs, and you have access to a building with N floors from 1 to N. 

Each egg is identical in function, and if an egg breaks, you cannot drop it again.

You know that there exists a floor F with 0 <= F <= N such that any egg dropped at a floor higher than F will break, and any egg dropped at or below floor F will not break.

Each move, you may take an egg (if you have an unbroken one) and drop it from any floor X (with 1 <= X <= N). 

Your goal is to know with certainty what the value of F is.

What is the minimum number of moves that you need to know with certainty what F is, regardless of the initial value of F?
-----------------------------------------
分析：
- "with certainty" 一定是最坏情况下，搜索区间穷尽时，而不是碰运气
- 就是说，对于每种搜索方案，每次都按最坏情况算，到最后的总次数最少的方案
- 动态规划求解，递归实现

状态转移方程：

dp(K, N) = min[1<=i<=N] { 1 + max { dp(K-1, i-1), dp(K, N-i) } }

base case:
dp(1,N) = N
dp(K,0) = 0

*/

// 超时
class Solution {
    unordered_map<int, int> dp;  // 哈希表存 dp 表
public:
    int superEggDrop(int K, int N) {
        if (K==1) return N;
        if (N==0) return 0;
        
        if (dp.find(N*100+K)!=dp.end()) return dp[N*100+K];  // 两个关键字压缩成一个
        
        int res = INT_MAX;
        for (int i=1;i<=N;++i) {
            res = std::min(res,  std::max(superEggDrop(K-1, i-1), superEggDrop(K, N-i)) + 1 );
        }
        
        dp[N*100+K] = res;
        
        return res;
    }
};

// 二分优化