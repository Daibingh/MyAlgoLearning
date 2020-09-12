#include "utils.hpp"

using namespace std;

/*
给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素

*/

// 基础解法
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int,int> m;
        for (const auto& t : nums) {
            ++m[t];
            if (m[t]> n/2) return t;
        }
        return 0;
    }
};


// **摩尔投票法**：
// 核心就是对拼消耗。
class Solution2 {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        int cand = nums[0];
        int cnt = 1;
        for (int i=1;i<n;++i) {
            if (cand == nums[i])
                ++cnt;   // 相同计数累加
            else {
                --cnt;  // 不同相互抵消
                if (!cnt) {
                    cand = nums[i];
                    cnt = 1;
                }
            }
        }
        return cand;  
    }
};