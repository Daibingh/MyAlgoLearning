#include "utils.hpp"
using namespace std;

/*
给定一个范围在  1 ≤ a[i] ≤ n ( n = 数组大小 ) 的 整型数组，数组中的元素一些出现了两次，另一些只出现一次。

找到所有在 [1, n] 范围之间没有出现在数组中的数字。

您能在不使用额外空间且时间复杂度为O(n)的情况下完成这个任务吗? 你可以假定返回的数组不算在额外空间内。

示例:

输入:
[4,3,2,7,8,2,3,1]

输出:
[5,6]

*/


// 数组原地 hash
class Solution2 {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n=nums.size();
        //使用原地hash的思想，将元素首先放到对应的位置
        for(int i=0;i<n;i++) {
            if(nums[i]!=i+1) {
                // 2,1,2,4,5
                // 1,2,2,4,5
                while(nums[i]!=nums[nums[i]-1]) {
                    swap(nums[i],nums[nums[i]-1]);
                }
            }
        }
        vector<int>res;
        for(int  i=0;i<n;i++){
            if(nums[i]!=i+1)res.push_back(i+1);
        }
        return res;
    }
};


// 对应位置取负数
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = nums.size();
        for (int i=0;i<n;++i) {
            nums[ abs(nums[i])-1 ] = - abs( nums[ abs(nums[i])-1 ] );
        }
        vector<int>res;
        for (int i=0;i<n;++i) {
            if (nums[i]>0) res.push_back(i+1);
        }
        return res;
    }
};
