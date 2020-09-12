#include "utils.hpp"

using namespace std;

/*
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

示例:

输入: [0,1,0,3,12]
输出: [1,3,12,0,0]
说明:

必须在原数组上操作，不能拷贝额外的数组。
尽量减少操作次数。
-----------------------------------
- partition 操作的实现，通过扫描和交换元素，将数组分割成两个区域 左侧满足某个条件
*/

// 双指针法，不是很高效的写法
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int l = 0; // 指向当前第一个 0
        int r = 0;  // 下一个非零
        while (r<nums.size()) {
            while (l<nums.size() && nums[l]!=0) ++l;
            r = l;
            while (r<nums.size() && nums[r]==0) ++r;
            if (r<nums.size()) swap(nums[l], nums[r]);
        }
    }
};


// 类似与 partition 操作，三颜色排序问题
// 在一个循环中扫描数组，i 当前要处理的位置，
// j 满足条件与不满足条件的分界线，i 要做的就是进行交换，使得 *i 在合适的位置
// [...j,0,0,0,i...]
class Solution2 {
public:

    // [0,j) 非零区;  [j,~] 零区
    void moveZeroes(vector<int>& nums) {
        int j = 0;
        for (int i=0;i<nums.size();++i) {
            if (nums[i]!=0) { // 遇到非零元，放到非零区后面
                swap(nums[j], nums[i]);
                ++j;
            }
        }
        
    }
};


class Solution3 {
public:
    void moveZeroes(vector<int>& nums) {
        stable_partition(nums.begin(), nums.end(), [](int a) {return a!= 0;});
    }
};