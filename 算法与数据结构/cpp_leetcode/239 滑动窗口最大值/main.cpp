#include "utils.hpp"

using namespace std;

/*
给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

返回滑动窗口中的最大值。
*/


// 单调队列解法，大个往前走, 小的删除，双端队列实，滑动窗口最大值
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> res;
        deque<int> dq;
        for (int i=0;i<k;++i) {
            push(dq, nums[i]);
        }
        res.push_back(dq.front());
        pop(dq, nums[0]);
        for (int i=k;i<n;++i) {
            push(dq, nums[i]);
            res.push_back(dq.front());
            pop(dq, nums[i-k+1]);
        }
        return res;
    }

    void push(deque<int>& dq, int val) {
        while (!dq.empty() && val > dq.back()) 
            dq.pop_back();
        dq.push_back(val);
    }

    void pop(deque<int>& dq, int val) {
        if (val == dq.front())
            dq.pop_front();
    }
};