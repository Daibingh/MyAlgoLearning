#include "utils.hpp"

using namespace std;


/*
给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

示例:

输入: [-2,1,-3,4,-1,2,1,-5,4],
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
----------------------------------------

- 求最大连续子序列的和
- 动态规划算法：O(n)
- 类似的题目：最长递增子序列(300)，最长公共子串，编辑距离
*/


class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> dp(nums.size(), 0);  // 表示以 i 结尾的最大连续子序列和
        dp[0] = nums[0];
        int res = nums[0];
        for (int i=1;i<nums.size();++i) {
            dp[i] = std::max(nums[i], dp[i-1]+nums[i]);  // 递推公式：dp[i] 分两种情况：1) nums[i] 是 dp[i-1] 最大子序列的一部分；2) nums[i] 是新的开始
            res = std::max(res, dp[i]);  // 记录最大值
        }
        return res;
    }
};

// 优化空间复杂度
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = 0;
        int res = INT_MIN;
        for (auto & t : nums) {
            if (sum < 0) {
                sum = t;
            }
            else sum += t;
            res = max(res, sum);
        }
        return res;
    }
};



/////////////////////////////////////////求编辑距离///////////////////////////////////////////
#include <bits/stdc++.h>

using namespace std;

int findMin(int a, int b, int c) {
    return std::min(a, std::min(b,c) );
}

int main() {
    string s1,s2;
    while (getline(cin, s1)) {
        getline(cin, s2);
        s1.insert(0, 1, ' ');  // 前面插入空格，便于初始化
        s2.insert(0, 1, ' ');
        
        vector<vector<int>> dp(s1.size(), vector<int>(s2.size(), 0));  // s1:[0, i], s2:[0,j] 子问题的解
        
        for (int i=0;i<s2.size();++i) {  // 初始（边界）条件
            dp[0][i] = i;
        }
        
        for (int i=0;i<s1.size();++i) {   // 初始（边界）条件
            dp[i][0] = i;
        }
        
        for (int i=1;i<s1.size();++i) {
            for (int j=1;j<s2.size();++j) {
                if (s1[i]==s2[j])  {  // s1[i]==s2[j], dp[i][j] = dp[i-1][j-1]
                    dp[i][j] = dp[i-1][j-1];
                } else {  // s1[i]!=s2[j], 分三种情况: 1) 删除[i]; 2) 删除[j]; 3) 交换[i][j], 取这三种情况最小值
                    dp[i][j] = findMin(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]) + 1;  
                }
            }
        }
        cout<<dp.back().back()<<endl;
    }
}

//////////////////////////////////求最长递增子序列///////////////////////////////////////
#include <bits/stdc++.h>

using namespace std;

int main() {
    int num;
    int h;
    while(cin>>num) {
        int res = 0;  // 对于每个 case 都要置零
        vector<int> dp(num, 1);  // 以 i 结尾的最长递增子序列长度
        vector<int> arr(num, 0);
        for (int i=0;i<num;++i) {
            cin>>h;
            arr[i] = h;
            for (int j=0;j<i;++j) {
                if (h>arr[j]) {
                    dp[i] = std::max(dp[i], dp[j]+1);  // 更新 dp[i]
                }
            }
            res = std::max(res, dp[i]);  // 更新最长的值
        }
        cout<<res<<endl;
    }
}

////////////////////////////////////最长公共子串/////////////////////////////////////////
int solve(string s1, string s2) {
    vector<vector<int>> dp(s1.size(), vector<int>(s2.size(), 0));  // dp[i][j] 表示 s1 以 i 结尾，s2 以 j 结尾的最长公共子串长度
    int n = 0;
    for (int i=0;i<s2.size();++i) {
        if (s1[0]==s2[i]) dp[0][i] = 1;  // 处理边缘
    }
    for (int i=0;i<s1.size();++i) {   // 处理边缘
        if (s2[0]==s1[i]) dp[i][0] = 1;
    }
    for (int i=1;i<s1.size();++i) {
        for (int j=1;j<s2.size();++j) {
            if (s1[i]==s2[j]) {
                dp[i][j] = dp[i-1][j-1]+1;
                n = std::max(n, dp[i][j]);
            }
        }
    }
    return n;
}


