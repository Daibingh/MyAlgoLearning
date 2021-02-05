# include "utils.hpp"

using namespace std;

/*
给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

说明：解集不能包含重复的子集。

示例:

输入: [1,2,2]
输出:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/subsets-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

// 遍历一个斜的树
class Solution {
    void helper(vector<int>& nums, int st, vector<int>& tmp, vector<vector<int>>& res) {
       res.push_back(tmp);
       for (int i=st; i<nums.size(); ++i) {
           if (i>st && nums[i]==nums[i-1]) continue;  // 去重，保证相同的兄弟节点不重复遍历
           tmp.push_back(nums[i]); 
           helper(nums, i+1, tmp, res);
           tmp.pop_back();
       }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        vector<int> tmp;
        helper(nums, 0, tmp, res);
        return res;
    }
};
