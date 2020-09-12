#include "utils.hpp"

using namespace std;


/*
在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

-----------------------------
解法：
- 排序
- 快排
- 堆
*/


// 解法 1：利用快排 定位基准元 的操作，减少搜索区间，基准位置等于 N-k 
class Solution {
public:
    
    int findKthLargest(vector<int>& nums, int k) {
        int target = nums.size()-k;
        int left = 0, right = nums.size()-1;
        while (true) {
           
            int idx = partion(nums, left,right);
            // cout<<"idx: "<<idx<<endl;
            //  print_vec(nums);
            if (idx==target) return nums[idx];  // 找到
            else if (idx<target) left = idx+1;  // 去右侧找
            else right = idx-1; // 去左侧找
        }
    }
    
    // 随机选择一个基准，并将其归位，左侧小于它，右侧大于它
    int partion(vector<int>& nums, int left, int right) {
        int idx = rand() % (right-left+1) + left;
        swap(nums[right], nums[idx]);
        int val = nums[right];
        int l = left, r = right;
        while (l < r) {
            while (l<r && nums[l] < val) ++l;
            while (l<r && nums[r]>=val) --r; // 这里必须包含 “=”
            swap(nums[l], nums[r]);
        }
        if (nums[l]>val) swap(nums[right], nums[l]);
        return l;
    }
};

// 解法 2： 堆排序的思路，建立 N 元大顶堆，然后弹出 k-1 次
class Solution2 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        buildHeap(nums);
        int heapSize = nums.size();
        for (int i=0;i<k-1;++i) {
            swap(nums[0], nums[heapSize-1]);
            filterDown(nums, 0, --heapSize);
        }
        return nums[0];
    }
    
    void buildHeap(vector<int>& nums) {
        for (int i=nums.size() / 2; i>=0; --i) {
            filterDown(nums, i, nums.size());
        }
    }
    
    void filterDown(vector<int>& nums, int idx, int size) {
        int chd = idx*2+1;
        int tmp = nums[idx];
        while (chd < size) {
            if (chd < size-1 && nums[chd+1] > nums[chd]) ++chd;
            if (tmp < nums[chd]) {
                nums[idx] = nums[chd];
                idx = chd;
                chd = 2*idx+1;
            } else break;
        }
        nums[idx] = tmp;
    }
};


// 解法 3：更巧妙的使用堆，建立 k 元小顶堆，用剩余元素更新 k 元小顶堆，最后堆顶就是 第 k 个最大的
class Solution3 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        buildHeap(nums, k);  // 前 k 个元素建立小顶堆
        for (int i=k;i<nums.size();++i) {  // 这里是从 下标 k 开始
            // print_arr(&nums[0], k);
            if (nums[i] > nums[0]) {  // 比堆顶大， 就插入顶，然后调整堆， 最终 前 k 个是全体最大的 k 个元素，而 堆顶又是 前 k 个中最小的一个
                nums[0] = nums[i];
                filterDown(nums, 0, k);
            }
        }
        return nums[0];
    }
    
    void buildHeap(vector<int>& nums, int n) {
        for (int i=n / 2; i>=0; --i) {
            filterDown(nums, i, n);
        }
    }
    
    void filterDown(vector<int>& nums, int idx, int size) {
        int chd = idx*2+1;
        int tmp = nums[idx];
        while (chd < size) {
            if (chd < size-1 && nums[chd+1] < nums[chd]) ++chd;
            if (tmp > nums[chd]) {
                nums[idx] = nums[chd];
                idx = chd;
                chd = 2*idx+1;
            } else break;
        }
        nums[idx] = tmp;
    }
};

/*
注：如果要求所有前 k 个最大的元素，以上都可以实现，法 2 可以做到有序输出，法 1、3 不行
*/

// 用 C++ 库函数 nth_element
class Solution4 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        nth_element(nums.begin(), nums.begin()+k-1, nums.end(), greater<int>());
        return nums[k-1];
    }
};


int main() {
    vector<int> a{3,5,7,1,0,6,8,11,32,9};
    auto res = Solution().findKthLargest(a, 6);
    print_vec(a);
    cout<<res<<endl;
}