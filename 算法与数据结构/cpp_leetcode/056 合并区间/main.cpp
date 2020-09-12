#include <bits/stdc++.h>
#include "utils.hpp"

using namespace std;

/*
题目：给出一个区间的集合，请合并所有重叠的区间。

示例 1:

输入: [[1,3],[2,6],[8,10],[15,18]]
输出: [[1,6],[8,10],[15,18]]
解释: 区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
------------------------------------------------
题解:
关键在于先对区间进行排序，这样可以保证合并的区间是**连续的**

*/


class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};
        std::sort(intervals.begin(), intervals.end()); // std::vector 重载了比较运算符，按照字典序比较
        vector<vector<int>> res;
        for (int i=0;i<intervals.size();++i) {
            if (res.empty() || res.back()[1]<intervals[i][0]) {  // 区间不重叠，直接放入结果集
                res.push_back(intervals[i]);
            } else {
                res.back()[1] = std::max(res.back()[1], intervals[i][1]);  // 区间有重叠，更新右区间
            }
        } 
        return res;
    }
};


int main() {

}