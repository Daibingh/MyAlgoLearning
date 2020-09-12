#include "utils.hpp"
using namespace std;


/*
普通二分查找
给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，
写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
*/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        while (l<=r) {
            int mid = l + (r-l)/2;
            if (nums[mid] == target) return mid;
            else if (nums[mid] < target) l = mid+1;
            else r = mid -1;
        }
        return -1;
    }
};


class Solution2 {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = findLeft(nums, target);
        int right = findRight(nums, target);
        return {left, right};
    }

    int findLeft(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        while (l<=r) {
            int mid = l + (r-l)/2;
            if (nums[mid] == target) r = mid-1;
            else if (nums[mid] < target) l = mid+1;
            else r = mid -1;
        }
        if (l < nums.size() && nums[l]==target) return l;
        return -1;
    }

    int findRight(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        while (l<=r) {
            int mid = l + (r-l)/2;
            if (nums[mid] == target) l = mid+1;
            else if (nums[mid] < target) l = mid+1;
            else r = mid -1;
        }
        if (r >=0 && nums[r]==target) return r;
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

