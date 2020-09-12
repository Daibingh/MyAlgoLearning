#include "utils.hpp"

using namespace std;



/*
给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
仅使用常数空间的一趟扫描算法
----------------------------------------------------
- 解法：快排三路 partion 操作
*/


class Solution {
public:
    void sortColors(vector<int>& a) {
        int l = 0, r = a.size();
        
        // [0, l) = 0; [l, r) = 1; [r, ~] = 2
        for (int i=0;i<r;) {
            if (a[i]==0) {
                swap(a[i], a[l]);
                ++l;
                ++i;
            }
            else if (a[i]==1) {
                ++i;
            }
            else {
                --r;
                swap(a[i], a[r]);
            }
        }
    }
};


// 三路快排, 分成 三个区域
pair<int,int> partion3(int* a, int left, int right) {
    int pivot = a[left];
    int l = left;
    int r = right+1;
    // 循环不变量：[~,l] < pivot; (l, r) = pivot; [r, ~] > pivot 
    for (int i=left+1;i<r;) {
        if (a[i]<pivot) {
            ++l;
            swap(a[i], a[l]);
            ++i;
        }
        else if (a[i]>pivot) {
            --r;
            swap(a[i], a[r]);
        }
        else {
            ++i;
        }
    }
    swap(a[l], a[left]);  // [~,l) < pivot; [l, r) = pivot; [r, ~] > pivot 
    return {l,r-1};
}