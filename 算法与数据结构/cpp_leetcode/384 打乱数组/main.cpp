#include "utils.hpp"

using namespace std;

/*
- 打乱一个没有重复元素的数组，要求每个位置上每个元素出现的概率是等可能的
--------------------------
思想：不放回黑箱摸球

- c++ list::iterator 不支持 + ， 使用 void std::advance(it, offset)
*/

class Solution {
    vector<int> backup;
    vector<int> nums;
public:
    Solution(vector<int>& nums) {
        backup = nums;
        this->nums = nums;
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return backup;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle2() {
        list<int> l(nums.begin(), nums.end());  // 需要创建额外空间
        for (int i=0;i<nums.size();++i) {
            int idx = rand()%l.size();
            auto it = l.begin();
            std::advance(it, idx);
            nums[i] = *(it);
            l.erase(it);
        }
        return nums;
    }
    
    //  Fisher-Yates 洗牌算法
     vector<int> shuffle() {
         int n = nums.size();
         for (int i=0;i<n;++i) {
             int idx = rand()%(n-i) + i;
             swap(nums[i], nums[idx]);  // 通过交换的方式，不需要额外空间
         }
         return nums;
     }
    
};
