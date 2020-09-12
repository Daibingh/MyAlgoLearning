
#include "utils.hpp"
using namespace std;


/*
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

Example:

Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
-------------------------------
解法：回溯法，有剪枝

*/

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
       vector<vector<int>> res;
        vector<int> item;
        helper(res, item, n, k);
        return res;
    }

    void helper(vector<vector<int>>& res, vector<int>& item, int n, int k) {
        if (item.size()==k) {
            res.push_back(item);
            return;
        }
        int i = item.empty() ? 1 : item.back() + 1;

        // k=4; n=8;
        // cnt = 1; rest = k-cnt = 3; cur < =n-2
        int limit = n-(k-item.size()-1);  // 剪枝， limit = n 没有剪枝
        for (;i<=limit;++i) {  // 组合 每次都从比上一个数大的开始遍历
            item.push_back(i);
            helper(res, item, n, k);
            item.pop_back();
        }
    }
};