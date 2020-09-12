#include <bits/stdc++.h>
using namespace std;

/*
给定一个整数数组 nums，按要求返回一个新数组 counts。数组 counts 有该性质： 
counts[i] 的值是  nums[i] 右侧小于 nums[i] 的元素的数量

*/


// Fenwick Tree
// 先离散化：将数值映射为 从1开始的连续的整数 ，根据排名
// 然后 进行 rank 计数，同时求前缀和 ==> 利用 Fenwick Tree 的 更新和查询操作
// 时间 O(nlogn)
// 空间 O(n)
class Solution {
	vector<int> tree;
public:
    vector<int> countSmaller(vector<int>& nums) {
    	set<int> sorted(nums.begin(), nums.end());  // 排序+去重
    	unordered_map<int,int> val2rank;
    	int rank = 1;
    	for (auto & t : sorted) {
    		val2rank[t] = rank++;
    	}
    	tree = vector<int>(rank, 0);
    	vector<int> res;
    	for (auto it=nums.rbegin();it!=nums.rend();++it) {  // 因为求右侧，所以要倒序遍历原始数组
            int  r = val2rank[*it];
    		update( r, 1);
    		res.push_back(query(r-1));
    	}
        reverse(res.begin(), res.end());   // 再次取反
    	return res;
    }

    void update(int i, int delta) {
    	while (i<tree.size()) {
    		tree[i] += delta;
    		i += lowbit(i);
    	}
    }

    int query(int i) {
    	int ret = 0;
    	while (i > 0) {
    		ret += tree[i];
    		i -= lowbit(i);
    	}
    	return ret;
    }

    static int lowbit(int x) {
    	return x & (-x);
    }
};


// 解法2: 利用 归并排序求逆序对数
class Solution2 {
    vector<int> tmp;
    vector<int> index;  // 索引同步排序，用于追踪原始数组的索引
    vector<int> tmpIndex;
    vector<int> res;
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        tmp = vector<int>(n);
        tmpIndex = vector<int>(n);
        index = vector<int>(n);
        res = vector<int>(n, 0);
        int i = 0;
        for (auto & t : index) t = i++;
        mergeSoft(nums, 0, nums.size()-1);
        // for (auto & t : nums) cout<<t<<" ";
        return res;
    }

    void mergeSoft(vector<int>& nums, int left, int right) {
        if (left>=right) return;
        int mid = left + (right-left)/2;
        mergeSoft(nums, left, mid);
        mergeSoft(nums, mid+1, right);
        int l = left, r = mid+1, k = left;
        while (l<=mid && r <= right) {
            if (nums[l]>nums[r]) {  // 从大到小排
                tmp[k] = nums[l];
                res[index[l]] += right-r+1;   // 对应逆序对数增加
                tmpIndex[k++] = index[l++];
            }
            else {
                tmp[k] = nums[r];
                tmpIndex[k++] = index[r++];
                
            }
        }
        while (l<=mid) {
            tmp[k] = nums[l];
            tmpIndex[k++] = index[l++];
        }
        while (r<=right) {
            tmp[k] = nums[r];
            tmpIndex[k++] = index[r++];
        }
        for (int i=left;i<=right;++i) {
            nums[i] = tmp[i];
            index[i] = tmpIndex[i];
        }
    }
};