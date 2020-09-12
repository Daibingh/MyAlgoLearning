#include "utils.hpp"
using namespace std;

/*
给定两个数组，编写一个函数来计算它们的交集。

示例 1：

输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2,2]
*/

// hash 表实现
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> numCnt1, numCnt2;
        for (const auto & t : nums1) {
            ++numCnt1[t];
        }
        for (const auto & t : nums2) {
            ++numCnt2[t];
        }
        vector<int> res;
        for (auto & m : numCnt1) {
            addNum(res, m.first, min(numCnt2[m.first], m.second));
        }
        return res;
    }

    void addNum(vector<int>& res, int val, int cnt) {
        for (int i=0;i<cnt;++i) res.push_back(val);
    }
};


// 使用 STL set_intersection
class Solution2 {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<int> result;
        set_intersection(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), back_inserter(result));
        return result;
    }
};
