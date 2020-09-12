#include <bits/stdc++.h>
using namespace std;


/*
中位数是有序列表中间的数。如果列表长度是偶数，中位数则是中间两个数的平均值。

例如，

[2,3,4] 的中位数是 3

[2,3] 的中位数是 (2 + 3) / 2 = 2.5

设计一个支持以下两种操作的数据结构：

void addNum(int num) - 从数据流中添加一个整数到数据结构中。
double findMedian() - 返回目前所有元素的中位数。
示例：

addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3) 
findMedian() -> 2
*/


// 使用 两个堆，一个大顶堆，一个小顶堆
// 关键在于平衡两个堆
class MedianFinder {
    priority_queue<int> q_left;  // 大顶堆
    priority_queue<int, vector<int>, greater<int>> q_right;  // 小顶堆
public:
    /** initialize your data structure here. */
    MedianFinder() {  }
    
    // 允许 小顶堆 个数比 大顶堆 多一个
    void addNum(int num) {
   		q_right.push(num);                   // 先放到小顶堆
       	q_left.push(q_right.top());          // 将小顶堆的顶移动到大顶堆，保证大顶堆的元素 <= 小顶堆
       	q_right.pop();
       	if (q_left.size()>q_right.size()) {  // 反过来调整
      		q_right.push(q_left.top());
      		q_left.pop();
       }
    }
    
    double findMedian() {
    	if (q_left.size()<q_right.size())
    		return q_right.top();
    	else 
    		return ( (q_left.empty() ? 0 : q_left.top() ) 
    			+ ( q_right.empty() ? 0 : q_right.top() ) ) / 2.;
    }		
};
