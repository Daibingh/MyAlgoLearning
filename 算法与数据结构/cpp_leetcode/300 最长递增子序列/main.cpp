#include "utils.hpp"

using namespace std;


/*
给定一个无序的整数数组，找到其中最长上升子序列的长度。

示例:

输入: [10,9,2,5,3,7,101,18]
输出: 4 
解释: 最长的上升子序列是 [2,3,7,101]，它的长度是 4。
说明:

可能会有多种最长上升子序列的组合，你只需要输出对应的长度即可。
你算法的时间复杂度应该为 O(n2) 。
进阶: 你能将算法的时间复杂度降低到 O(n log n) 吗?
----------------------------------------------

题解：

- 动态规划

*/


class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);  // dp[i] 表示以 i 结尾的最长递增子序列长度
        int res = 0;
        for (int i=0;i<nums.size();++i) {
            for (int j=0;j<i;++j) {
                if (nums[i]>nums[j]) {
                    dp[i] = std::max(dp[i], dp[j]+1);  // 递推：从前至后扫描，如果 nums[i]>nums[j] 则更新 dp[i]=max(dp[j]+1, dp[i])
                }
            }
            res = std::max(res, dp[i]); // 最后的 用 dp[i] 再更新总的最大值
        }
        return res;
    }
};

int main() {

}