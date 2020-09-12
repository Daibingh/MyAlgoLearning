#include "utils.hpp"

using namespace std;

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

// 双指针，定位 pivot 所在的位置，并使得 左侧小于 pivot, 右侧大于等于 pivot
int partion(int* a, int left, int right) {
    int pivot = a[right];
    int l = left, r = right-1;
    while (l<r) {
        while (l<r && a[l]<pivot) ++l;
        while (l<r && a[r]>=pivot) --r;
        swap(a[l], a[r]);
    }
    if (a[l]>pivot) swap(a[l], a[right]);
    return l;
}

// 单向扫描
int partion2(int* a, int left, int right) {
    int pivot = a[left];
    int l = left;
    // 循环不变量：[~,l] < pivot
    for (int i=left+1;i<=right;++i) {
        if (a[i]<pivot) {
            ++l;
            swap(a[i], a[l]);
        }
    }
    swap(a[l], a[left]);
    return l;
}


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


void quick_sort(int* a, int left, int right) {
    if (left>=right) return;
    int mid = partion2(a, left, right);
    quick_sort(a, left, mid-1);
    quick_sort(a, mid+1, right);
}


int main() {
    int a[] = {4,8,2,4,6,1,4,5};
    // quick_sort(a, 0, 5);
    int p1, p2;
    std::tie(p1, p2) = partion3(a, 0, 7);
    print_arr(a, 8);
    cout<<p1<<", "<<p2<<endl;
}