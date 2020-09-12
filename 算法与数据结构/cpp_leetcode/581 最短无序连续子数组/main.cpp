#include "utils.hpp"
using namespace std;

/*
给定一个整数数组，你需要寻找一个连续的子数组，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。

你找到的子数组应是最短的，请输出它的长度。

示例 1:

输入: [2, 6, 4, 8, 10, 9, 15]
输出: 5
解释: 你只需要对 [6, 4, 8, 10, 9] 进行升序排序，那么整个表都会变为升序排序。

*/


// 时间 O(n); 空间 O(1)
// 先找无序的最小范围 端点处不满足大小关系
// 1, 5, | 6,  4, 8, 3, 10, 9, | 11, 15
//           min: 3, max: 10
// 然后向两侧拓展边界
class Solution2 {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        if (nums.size() <2 ) return 0;
        int l = 0, r = nums.size()-1;
        for (;l<nums.size()-1;++l) {
            if (nums[l]>nums[l+1]) break;
        }
        for (; r>0;--r) {
            if (nums[r] < nums[r-1]) break;
        }
        if (l>r) return 0;
        int minVal = INT_MAX, maxVal = INT_MIN;
        for (int i=l;i<=r;++i) {
            minVal = min(minVal, nums[i]);
            maxVal = max(maxVal, nums[i]);
        }
        while ( l >0 && minVal<nums[l-1]  ) --l;
        while ( r<nums.size()-1 && maxVal>nums[r+1] )  ++r;
        return r-l+1;
    }

};

/*
从左到右循环，记录最大值为 max，若 nums[i] < max, 则表明位置 i 需要调整, 循环结束，
记录需要调整的最大位置 i 为 high; 
同理，从右到左循环，记录最小值为 min, 若 nums[i] > min, 
则表明位置 i 需要调整，循环结束，记录需要调整的最小位置 i 为 low.
*/
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int len = nums.size();
        if(len <= 1) return 0;
        int high = 0, low = len-1, maxVal = nums[0], minVal = nums[len-1];
        for(int i = 1; i < len; i++){
            maxVal = max(maxVal, nums[i]);
            minVal = min(minVal, nums[len-1-i]);
            if(nums[i] < maxVal) high = i;
            if(nums[len-1-i] > minVal) low = len-1-i;
        }
        return high > low ? high - low + 1 : 0;
    }
};