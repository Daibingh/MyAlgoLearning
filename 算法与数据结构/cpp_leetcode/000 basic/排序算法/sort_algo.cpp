#include "utils.hpp"

// using namespace std;

/*
- 冒泡排序、快速排序 函数模板
*/

template<typename T>
inline void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}


// 1. 冒泡排序
// 时间复杂度：n^2; 空间复杂度：1
// 稳定

template<typename T>
void maopao_sort(T* begin, T* end, std::function<bool(const T&,const T&)> comp = [](const T& a, const T& b) {return a < b;}) {
    /*
    通过前移 end 指针，不断的缩短长度；通过指针比较控制循环次数
    */
    bool swaped = true;
    while (end-begin>1 && swaped)  // 外循环控制通过比较 begin 与 end，当长度大于 1 时，要继续进行排序，同时看看上一轮交换标志。
    {
        T* curr = begin;
        swaped = false;
        while (curr<end-1) {
            if (comp(*(curr+1), *curr)) {  
                swap(*curr, *(curr+1)); 
                swaped = true;
            }
            ++curr;
        }
        --end;
    }
}

// 2. 快排（递归版本）
// 时间复杂度：nlog(n); 空间复杂度：nlog(n)
// 不稳定

template<typename T>
void quick_sort(T *begin, T* end, std::function<bool(const T&,const T&)> comp = [](const T& a, const T& b) {return a < b;})
{
    if (end-begin <= 1) return;
    T* left = begin, *right = end-1;
    T val = *(end-1);  // 选取 *(end-1) 为基准 val
    while (left < right) {  // 双指针法从两端走向中间，保证 *left<val, *right>val, 否则交换
        while (left < right && comp(*left, val)) ++left;
        while (left < right && !comp(*right, val)) --right;
        swap(*left, *right);
    }
    if (comp(val, *left)) swap(*left, *(end-1));  // 保证 left 左侧都小于 *left, 右侧都大于 *left
    quick_sort(begin, left);  // 以 left 为界限，对两侧区间进行排序（不包含 left）
    quick_sort(left+1, end);
}

int main() {
    std::vector<int> data = {7,1,4,3,5,2,2,5};
    // maopao_sort(&data[0], &data[0]+data.size());
    quick_sort(&data[0], &data[0]+data.size());
    print_vec(data);
}