#include "utils.hpp"
using namespace std;

/*
给定一个无序的数组 nums，将它重新排列成 nums[0] < nums[1] > nums[2] < nums[3]... 的顺序。

示例 1:

输入: nums = [1, 5, 1, 1, 6, 4]
输出: 一个可能的答案是 [1, 4, 1, 5, 1, 6]
*/

// 此题是思路不好想
// 将数组分成 左右 两个部分，左<=右
// 然后先各自反序，再相互穿插

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        int n1 = (n+1)/2;  // 左侧个数
        sort(nums.begin(), nums.end());
        vector<int> tmp1(nums.begin(), nums.begin()+n1);
        vector<int> tmp2(nums.begin()+n1, nums.end());
        reverse(tmp1.begin(), tmp1.end());
        reverse(tmp2.begin(), tmp2.end());
        int j = 0;
        for (int i=0;i<n/2;++i) {
            nums[j++] = tmp1[i];
            nums[j++] = tmp2[i];
        }
        if (n&1) nums[j] = tmp1[n1-1];
    }
};


// 找中位数 nth_element
// 三路划分 [<mid][=mid][>mid] 
// 避免区域内部排序
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int  n = nums.size();
        int n1 = (n+1)/2;
        nth_element(nums.begin(), nums.begin()+n1-1, nums.end() );
        int mid = nums[n1-1];

        // [<mid][==mid][>mid]
        // ====>
        // 三路划分
        int l = 0, r = nums.size()-1, i=0;
        while ( i<=r ) {
            if (nums[i] <mid ) {
                swap( nums[i++], nums[l++] );
            }
            else if ( nums[i]==mid ) {
                ++i;
            }
            else {
                swap(nums[i], nums[r--]);
            }
        }
        vector<int> tmp1(nums.begin(), nums.begin()+n1);
        vector<int> tmp2(nums.begin()+n1, nums.end());
        reverse(tmp1.begin(), tmp1.end());
        reverse(tmp2.begin(), tmp2.end());
        int j = 0;
        for (int i=0;i<n/2;++i) {
            nums[j++] = tmp1[i];
            nums[j++] = tmp2[i];
        }
        if (n&1) nums[j] = tmp1[n1-1];
    }
};