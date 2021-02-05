#include <bits/stdc++.h>
using namespace std;

/*
老师想给孩子们分发糖果，有 N 个孩子站成了一条直线，老师会根据每个孩子的表现，预先给他们评分。
你需要按照以下要求，帮助老师给这些孩子分发糖果：
每个孩子至少分配到 1 个糖果。
相邻的孩子中，评分高的孩子必须获得更多的糖果。
那么这样下来，老师至少需要准备多少颗糖果呢？

*/

// 正反向扫描
class Solution {
public:
    int candy(vector<int>& r) {
        int n = r.size();
        vector<int> res(n, 1);
        for (int i=0;i<n-1;++i) {
            if (r[i]<r[i+1]) {  // 正向扫描，后比前大，就比前多 1，满足右规则
                res[i+1] = res[i]+1;
            }
        }
        for (int i=n-1;i>0;--i) {
            if (r[i-1]>r[i] && res[i-1]<=res[i]) {  // 反向扫描，前比后大，且前面的糖的个数<=后者，比后者多 1，满足左规则
                res[i-1] = res[i]+1;
            }
        }
        return accumulate(res.begin(), res.end(), 0);  // 返回累加值
    }
};