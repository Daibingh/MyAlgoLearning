#include <bits/stdc++.h>
using namespace std;

/*
Binary Indexed Tree OR Fenwick Tree (树状数组)
**实现可更改的数组中快速进行 range sum query **
- 时间 update: O(logn) ; query: O(logn)
- 空间 O(n)

数组形式存储，更新和查询 是 树 的遍历的形式，实际上是虚拟的树，操作中存在树的逻辑，实际没有树的形态

*/

class FenwickTree {
    vector<int> arr;
    
    int lowbit(int x) { return x & (-x); }  // x & (-x) 取出最低位的 “1”

public:
    FenwickTree(int n): arr(n+1, 0) {}  // 下标从 “1” 开始

    void update(int idx, int delta) {  // 这里更新的是 变化量，不是绝对值！！！
        while (idx < arr.size()) {
            arr[idx] += delta;
            idx += lowbit(idx);
        }
    }

    int query(int idx) {
        int ret = 0;
        while (idx > 0 )
        {
            ret += arr[idx];
            idx -= lowbit(idx);
        }
        return ret;
    }

};

// 应用：leetcode: 307. Range Sum Query - Mutable

class NumArray {
    vector<int> arr;  // 存树
    vector<int> bak;  // 存数据
    int lowbit(int x) { return x & (-x); }  // x & (-x) 取出最低位的 “1”
public:
    NumArray(vector<int>& nums): arr(nums.size()+1, 0),bak(nums.size(),0) {
        int i=0;
        for (auto & t : nums) update(i++, t);
}
    
    void update(int idx, int val) {
        int del = val - bak[idx];
        bak[idx] = val;
        idx += 1;
        while (idx < arr.size()) {
            arr[idx] += del;
            idx += lowbit(idx);
        }
    }

    int query(int idx) {
        int ret = 0;
        while (idx > 0 )
        {
            ret += arr[idx];
            idx -= lowbit(idx);
        }
        return ret;
    }
    
    int sumRange(int i, int j) {
        return query(j+1) -query(i);
    }
};


int main() {
    vector<int> a{1,2,3,4,5,6,7,8};
    FenwickTree ft(a.size());
    for (int i=0;i<a.size();++i) {
        ft.update(i+1, a[i]);
    }
    for (int i=1;i<=a.size();++i) {
        cout<< ft.query(i) <<endl;
    }
}
