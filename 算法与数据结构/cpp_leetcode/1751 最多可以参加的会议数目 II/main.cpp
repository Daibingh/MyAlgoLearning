
#include <bits/stdc++.h>

using namespace std;

/*

定义 dp[i][j] : 前i个会议中最多参加

dp[i][j] = max( dp[i-1][j], dp[k][j-1]+e[i][2] ), k = binarySearch(...)

边界条件：
dp[0][j] = 0
dp[i][0] = 0

*/

// 暴力搜索
class Solution {
    int res;
public:
    int maxValue(vector<vector<int>>& events, int k) {
        sort( events.begin(), events.end(), []( const vector<int>& a, const vector<int>& b  ){ return a[1]<b[1]; } );
        res = 0;
        helper(events, k, -1, 0);
        return res;
    }
    
    void helper(vector<vector<int>>& events, int k, int st, int sum) {
        res = max(res, sum);
        if (k==0) return ;
        for (int i=st+1; i<events.size(); ++i) {
            if ( st==-1 || events[i][0]>events[st][1])
                helper(events, k-1, i, sum+events[i][2]);
        }
    }
};

// 动态规划，类似背包问题
class Solution {
public:
    int maxValue(vector<vector<int>>& e, int k) {
       vector<vector<int>> dp(e.size()+1, vector<int>(k+1));
       sort( e.begin(), e.end(), []( const vector<int>& a, const vector<int>& b  ){ return a[1]<b[1]; } );
       // 预存
       vector<int> cached(e.size());
       for (int i=0;i<e.size();++i) {
           cached[i] = find(e, i);
       }
       for (int i=1; i<e.size()+1; ++i) {
           for (int j=1; j<k+1; ++j) {
               dp[i][j] = max( dp[i-1][j], dp[cached[i-1]+1][j-1]+e[i-1][2] );
           }
       }
       return dp.back().back();
    }

    // 二分搜索，从右到左第一个小于e[k][0]的元素
    int find(vector<vector<int>>& e, int k) {
        int r = k-1, l = -1;
        while (l<r) {
            int mid = (l+r+1)/2;  // 注意！
            if (e[mid][1]>=e[k][0]) r=mid-1;
            else l = mid;
        }
        return l;
    }
};