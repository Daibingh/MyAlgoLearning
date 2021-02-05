#include "utils.hpp"

using namespace std;

/*
Given a set of distinct integers, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

Example:

Input: nums = [1,2,3]
Output:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
--------------------------------------------------------------------------
分析：
- 求给定集合的所有子集
- 常见的方法回溯法，子集问题的回溯法的两种写法
- 相似问题：排列，组合
*/


// 回溯法第一种写法：模拟 二叉树的遍历，遍历到底部才添加结果
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> item;
        helper(res, item, nums, 0);
        return res;
    }

    void helper(vector<vector<int>>& res, vector<int>& item, vector<int>& nums, int i) {
        // 遍历完所有的数，添加得到的子集到结果集
        if (i==nums.size()) {
            res.push_back(item);
            return;
        }
        // 对于第 i 个数，有两种选择：1) 加入当前子集 2) 不加入当前子集
        helper(res, item, nums, i+1); // 不加，直接往下递归
        item.push_back(nums[i]); // 加入
        helper(res, item, nums, i+1); // 往下递归
        item.pop_back();  // 撤销选择
    }
};


// 回溯法第二种写法：有条件的N叉树的遍历，写法与组合问题相似, 不同之处在于添加结果的处理不同
class Solution2 {
public:
    vector<vector<int>> res;

vector<vector<int>> subsets(vector<int>& nums) {
    // 记录走过的路径
    vector<int> track;
    backtrack(nums, 0, track);
    return res;
}

void backtrack(vector<int>& nums, int start, vector<int>& track) {
    // 每次回溯，直接添加结果
    res.push_back(track);
    for (int i = start; i < nums.size(); i++) {  // 通过 start 避免子集重复
        // 做选择
        track.push_back(nums[i]);
        // 回溯
        backtrack(nums, i + 1, track);
        // 撤销选择
        track.pop_back();
    }
}
    
};

//                     []
//         1           2           3
//     2       3       3   
// 3                


// 迭代的方法
class Solution3 {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;  // 最后的结果集
        vector<vector<int>> tmp;  // 上一层结果集（长度为 i）
        res.push_back( vector<int>() );
        tmp.push_back( vector<int>() );
        for (int i=0;i<nums.size(); ++i) {
            vector<vector<int>> tmp_new;  // 下一层结果集，（长度为 i+1）
            for (const auto & v : tmp) {
                for (const auto & t : nums) {
                    if ( v.empty() || t > v.back() ) {  // 添加新元素，要求比最后一个元素大
                        vector<int> item = v;
                        item.push_back(t);
                        tmp_new.push_back(item);
                        res.push_back(item);
                    }
                }
            }
            tmp = tmp_new;  // 更新上一层结果集
        }
        return res;
    }
};

// 动态规划的思想，根据前n个数的子集，退出n+1个数的子集
class Solution4 {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res{{}};
        for (const auto & n : nums) {
            int size = res.size();
            for (int i=0; i<size; ++i) {
                auto t = res[i];
                t.push_back(n);
                res.push_back(t);
            }
        }
        return res;
    }
};