#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> tmp;
        helper(res, tmp, nums);
        return res;
    }

    void helper(vector<vector<int>>& res, vector<int>& tmp, vector<int>& nums) {
        if ( tmp.size() == nums.size() ) {
            res.push_back(tmp);
            return;
        }
        for (int i=0; i<nums.size(); ++i) {
            if (nums[i]==-100) continue;
            tmp.push_back(nums[i]);
            int bak = nums[i];
            nums[i] = -100;
            helper(res, tmp, nums);
            tmp.pop_back();
            nums[i] = bak;
        }
    }
};


int main() {
    
}