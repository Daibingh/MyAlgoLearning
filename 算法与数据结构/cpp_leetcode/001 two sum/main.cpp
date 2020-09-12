#include "utils.hpp"

using namespace std;

/**
 *  采用 hash 表，以值作为 key，索引作为 value，遍历的同时，建表查表；
 *  时间复杂度 O(n), 空间复杂度 O(n)；
 *  想采用排序+双指针，但是排序后索引发生改变，不能用
 * 
 */

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        if (nums.empty()) {
            return {-1,-1};
        }
        unordered_map<int,int> val2ind(nums.size());
        for (auto i=0;i<nums.size();++i) {
            auto it = val2ind.find(target-nums[i]);  // unorder_map find 找到返回 iterator，否则返回 end of iterator.
            if (it!=val2ind.end()) {
                return {it->second,i};
            val2ind[nums[i]] = i;
        }
        return {-1,-1};
    }
};

int main () {
    vector<int> v{0, 2, 1, 6, 7, 9, 4};
    auto res = Solution().twoSum(v, 11);
    print_vec(res);
}