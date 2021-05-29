#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int n = nums.size();
        if (n==3) return nums[0] * nums[1] * nums[2];
        std::sort(nums.begin(), nums.end());
        int res1 = nums[n-1] * nums[n-2] * nums[n-3];
        int res2 = nums[n-1] * nums[1] * nums[0];
        return std::max(  res1 , res2 ) ;
    }
};

// -6 -5 -1 2 3 4 7

int main() {

}