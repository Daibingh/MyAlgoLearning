#include "utils.hpp"
using namespace std;

/*
给定一个整数数组，判断是否存在重复元素。

如果任意一值在数组中出现至少两次，函数返回 true 。如果数组中每个元素都不相同，则返回 false 。
*/

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> S;
        for (auto & t : nums) {
            if (S.count(t)) return true;
            S.insert(t);
        }
        return false;
    }
};