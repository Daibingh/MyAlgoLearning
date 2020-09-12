#include "utils.hpp"

using namespace std;


/*给定一个非空的整数数组，返回其中出现频率前 k 高的元素
你可以假设给定的 k 总是合理的，且 1 ≤ k ≤ 数组中不相同的元素的个数。
你的算法的时间复杂度必须优于 O(n log n) , n 是数组的大小。
题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的。
你可以按任意顺序返回答案。

*/


// 优先队列实现
struct Ele {
    int val;
    int cnt;
    bool operator < (const Ele& e) const {   // 这里必须加 const
        return cnt < e.cnt;
    }
};

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        for (const auto & t : nums) {
            ++m[t];
        }
        priority_queue<Ele> q;
        for (const auto & t : m) {
            q.push({t.first, t.second});
        }
        vector<int> res;
        for (int i=0;i<k;++i) {
            res.push_back(q.top().val);  // 优先队列是 top() 不是 front()
            q.pop();
        }
        return res;
    }
};