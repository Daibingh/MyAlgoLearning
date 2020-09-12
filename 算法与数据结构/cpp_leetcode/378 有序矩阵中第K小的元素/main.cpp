#include "utils.hpp"
using namespace std;

/*
给定一个 n x n 矩阵，其中每行和每列元素均按升序排序，找到矩阵中第 k 小的元素。
请注意，它是排序后的第 k 小元素，而不是第 k 个不同的元素。
*/


// 维护 k 元大顶堆
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        vector<int> heap(k);
        int n = matrix.size();
        int i = 0;
        for (;i<k;++i) {
            heap[i] = matrix[i/n][i%n];
        }
        make_heap(heap.begin(), heap.end());
        for (;i<n*n;++i) {
            int val = matrix[i/n][i%n];
            if (val < heap[0]) {
                pop_heap(heap.begin(), heap.end());
                heap[k-1] = val;
                push_heap(heap.begin(), heap.end());
            }
        }
        return heap[0];
    }
};


///////////////////////////////////////////////////
// 多路归并，使用优先队列
// 思路：队列头是剩余最小元，队头出队，将它的下一个元素入队
struct Ele
{
	int y,x,val;
	bool operator < (const Ele& e) const {
		return this->val > e.val;
	}
	
};


class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
    	priority_queue<Ele> q;
    	int n = matrix.size();
    	for (int i=0;i<n;++i) {
    		q.push( {i, 0, matrix[i][0]} );
    	}
    	for (;k>1;--k) {
    		auto t = q.top();
    		q.pop();
    		if (t.x+1<n) q.push({t.y, t.x+1, matrix[t.y][t.x+1]});
    	}
    	return q.top().val;
    }
};
