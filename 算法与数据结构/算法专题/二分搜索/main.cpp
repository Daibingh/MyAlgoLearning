#include <bits/stdc++.h>

using namespace std;

// 1. simple binary search
int search(const vector<int>& a, int val) {
    int l = 0, r = a.size()-1;
    int m;
    while (l<=r) {
        m = l + (r-l)/2;
        if (a[m]==val) return m;
        else if (a[m]<val) l = m+1;
        else r = m-1;
    }
    return -1;
}

// 2. lower_bound
int firstGeFromLeft(const vector<int>& a, int val) {
    int l = 0, r = a.size();
    int m;
    while (l<r) {
        m = l + (r-l)/2;
        if (a[m]<val) l = m+1;
        else r = m;
    }
    return l;
}

// upper_bound
int firstGtFromLeft(const vector<int>& a, int val) {
    int l = 0, r = a.size();
    int m;
    while (l<r) {
        m = l + (r-l)/2;
        if (a[m]<=val) l = m+1;
        else r = m;
    }
    return l;
}

// 3. 从右侧找第一个小于 val 的元素
int firstLtFromRight(const vector<int>& a, int val) {
    int l = -1, r = a.size()-1;
    int m;
    while (l<r) {
        m = l + (r-l+1)/2;
        if (a[m]>=val) r = m-1;
        else l = m;
    }
    return l;
}

// 从右侧找第一个小于等于 val 的元素
int firstLeFromRight(const vector<int>& a, int val) {
    int l = -1, r = a.size()-1;
    int m;
    while (l<r) {
        m = l + (r-l+1)/2;
        if (a[m]>val) r = m-1;
        else l = m;
    }
    return l;
}


int main() {
    vector<int> a{1,2,2,2,3,4,5};

    cout<<firstLtFromRight(a, 0)<<endl;
}