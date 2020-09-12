#include <bits/stdc++.h>
#include "utils.hpp"

using namespace std;

// backtracking 超出时间限制的解法
class Solution {

    vector<int> nums;

public:
    bool canJump(vector<int>& nums) {
        this->nums = nums;
        return backtracking();
    }

    bool backtracking(int i=0) {
        if (i == nums.size()-1) return true;
        for (int k=1;k<=nums[i]; ++k) {
            if (i+k < nums.size() && backtracking(i+k)) {
                return true;
            }
        }
        return false;
    }
};


// 动态规划 还超时间！
class Solution2 {


public:
    bool canJump(vector<int>& nums) {
        if (nums.size()==1) return true;
        vector<int> flag(nums.size(), 0);
        flag[nums.size()-1] = 1;
        for (int i=nums.size()-2;i>=0;--i) {
            for (int k=1;k<=nums[i];++k) {
                if (i+k<nums.size() && flag[i+k]) {
                    flag[i] = true;
                    break;
                }
            }
        }
        return flag[0];
    }

};

// 贪心思想，通过维护最远可到达的范围，并与目标距离比较，没必要 DFS
class Solution3 {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int rightmost = 0;  // 遍历到前 i 个点时，所能到达的最远位置
        for (int i = 0; i < n; ++i) {
            if (i <= rightmost) {
                rightmost = max(rightmost, i + nums[i]);
                if (rightmost >= n - 1) {
                    return true;
                }
            }
        }
        return false;
    }
};


int main() {
    vector<int> a{3,2,1,0,4};
    cout<<Solution3().canJump(a)<<endl;
}