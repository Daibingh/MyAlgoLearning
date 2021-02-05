#include "utils.hpp"

using namespace std;


/*
你将获得 K 个鸡蛋，并可以使用一栋从 1 到 N  共有 N 层楼的建筑。

每个蛋的功能都是一样的，如果一个蛋碎了，你就不能再把它掉下去。

你知道存在楼层 F ，满足 0 <= F <= N 任何从高于 F 的楼层落下的鸡蛋都会碎，从 F 楼层或比它低的楼层落下的鸡蛋都不会破。

每次移动，你可以取一个鸡蛋（如果你有完整的鸡蛋）并把它从任一楼层 X 扔下（满足 1 <= X <= N）。

你的目标是确切地知道 F 的值是多少。

无论 F 的初始值如何，你确定 F 的值的最小移动次数是多少？
---------------------------------------------------
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
class Solution2 {
    unordered_map<int, int> dp;
public:
    int superEggDrop(int K, int N) {
        if (K==1) return N;
        if (N==0) return 0;
        
        if (dp.count(N*100+K)) return dp[N*100+K];
        
        int res = 0;
        int l = 1, r = N;
        int z1=0, z2=0;
        // 二分
        while (l+1<r) {  // 注意终止条件
            int mid = l+(r-l)/2;
            z1 = superEggDrop(K-1, mid-1);  // 递增
            z2 = superEggDrop(K, N-mid);  // 递减
            if (z1==z2) {
                l=r=mid;
            }
            else if (z1<z2) {
                l = mid;  // 保留边界
            }
            else {
                r = mid;  // 保留边界
            }
        }
        z1 = max(superEggDrop(K-1, l-1), superEggDrop(K, N-l));
        z2 = max(superEggDrop(K-1, r-1), superEggDrop(K, N-r));
        res = max(z1, z2)+1;        
        return  dp[N*100+K] = res;
    }
};