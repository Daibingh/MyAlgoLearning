#include "utils.hpp"
using namespace std;

/*
给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

你的算法时间复杂度必须是 O(log n) 级别。

如果数组中不存在目标值，返回 [-1, -1]。

示例 1:

输入: nums = [5,7,7,8,8,10], target = 8
输出: [3,4]
示例 2:

输入: nums = [5,7,7,8,8,10], target = 6
输出: [-1,-1]
*/

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = findLeft(nums, target);
        int right = findRight(nums, target);
        return {left, right};
    }

    // 找左边界
    int findLeft(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        while (l<=r) {
            int mid = l + (r-l)/2;
            if (nums[mid] == target) r = mid-1;
            else if (nums[mid] < target) l = mid+1;
            else r = mid -1;
        }
        if (l < nums.size() && nums[l]==target) return l; // 如果 l 未越上界， nums[l]==target 返回 l
        return -1;
    }

    // 找右边界
    int findRight(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        while (l<=r) {
            int mid = l + (r-l)/2;
            if (nums[mid] == target) l = mid+1;
            else if (nums[mid] < target) l = mid+1;
            else r = mid -1;
        }
        if (r >=0 && nums[r]==target) return r;  // r 有可能越下界，判断 r 返回 r
        return -1;
    }
};


// 1,2,3,3,3,4,5  (3)
//   r,l          (左)
//         r,l    (右)

//   2,2    (1)
// r,l      (左/右)

//   2,2    (3)
//     r,l  (左/右)


// use C++ STL lower_bound and upper_bound
class Solution {
public:
    vector<int> searchRange(vector<int>& a, int t) {
        auto it1 = lower_bound(a.begin(), a.end(), t);
        auto it2 = upper_bound(a.begin(), a.end(), t);
        if (it1==it2) return {-1,-1};
        return { static_cast<int>(distance(a.begin(), it1)), static_cast<int>(distance(a.begin(), it2-1)) };
    }
};