/*
https://leetcode-cn.com/problems/container-with-most-water/
---

*/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size()-1;
        int res = min(height[l], height[r]) * (r-l);
        while (l < r) {
            if (height[l] < height[r]) {  // 移动小的一侧的指针
                ++l;
            } else {
                --r;
            }
            res = max(res, min(height[l], height[r]) * (r-l) );
        }
        return res;
    }
};