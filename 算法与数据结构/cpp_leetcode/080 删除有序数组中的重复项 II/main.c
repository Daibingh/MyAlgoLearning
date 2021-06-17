
/*
给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使每个元素 最多出现两次 ，返回删除后数组的新长度。
不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
*/



static inline void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}


// 双指针的典型应用
// 快指针(i)用于探索, 慢指针(j)维护结果边界
int removeDuplicates(int* nums, int numsSize){
    if (numsSize < 2) return numsSize;
    int j=2;
    for (int i=2;i<numsSize;++i) {
        if (nums[i]!=nums[j-2]) {
            swap(nums+i, nums+j);
            ++j;
        }
    }
    return j;
}