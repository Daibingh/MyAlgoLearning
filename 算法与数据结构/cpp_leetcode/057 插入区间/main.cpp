#include <bits/stdc++.h>
#include "utils.hpp"

using namespace std;

/*
给出一个无重叠的 ，按照区间起始端点排序的区间列表。
在列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间）。
--------------------------------------------
题解：
直接转化为上一个题！！！“转化思想”

*/


class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        intervals.push_back(newInterval);
        return merge(intervals);
    }

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
    vector<vector<int>> a={{1, 5}};
    vector<int> b = {6,8};
    auto res = Solution().insert(a,b);
    for (auto& t: res) {
        print_vec(t);
    }
    return 0;
}