#include <bits/stdc++.h>

using namespace std;

/*
有 n 个网络节点，标记为 1 到 n。

给你一个列表 times，表示信号经过 有向 边的传递时间。 times[i] = (ui, vi, wi)，其中 ui 是源节点，vi 是目标节点， wi 是一个信号从源节点传递到目标节点的时间。

现在，从某个节点 K 发出一个信号。需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 -1 。

*/

// 迪杰斯特拉算法
// 时间复杂度 O(E+V^2)
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> G(n+1);
        for (const auto & t : times) {
            G[t[0]].push_back({t[1], t[2]});
        }
        vector<int> known(n+1,0);
        vector<int> dist(n+1, INT_MAX);
        dist[k] = 0;
        int cnt = 1;
        while (cnt<n) {
            int u = findMin(known, dist);  // 线性搜索最小值, 适用于稠密图
            known[u] = 1;
            ++cnt;
            if (dist[u]==INT_MAX) continue;  // 最小值是 INT_MAX，说明后续未知点都不可达
            for (const auto p : G[u]) {
                int v = p.first, w = p.second;
                if (!known[v]) dist[v] = min(dist[v], dist[u]+w);  // 只更新未知节点
            }
        }
        int res = *max_element(dist.begin()+1, dist.end());
        return res == INT_MAX ? -1 : res;
    }

    int findMin(const vector<int>& known, const vector<int>& dist ) {
        int k = 0;
        int val = INT_MAX;
        for (int i=1;i<dist.size();++i) {
            if (known[i]) continue;
            if (dist[i]<val) {
                k = i;
                val = dist[i];
            }
        }
        return k;
    }
};


// 使用优先队列 使用于 稀疏图
struct Comp {
    bool operator() (const pair<int,int>& a, const pair<int,int>& b) {
        return a.second > b.second;
    }
};

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> G(n+1);
        for (const auto & t : times) {
            G[t[0]].push_back({t[1], t[2]});
        }
        vector<int> dist(n+1, INT_MAX);
        vector<int> known(n+1,0);
        priority_queue<pair<int,int>, vector<pair<int,int>>, Comp> q;
        q.push({k, 0});
        while (!q.empty()) {
            int u = q.top().first, w0 = q.top().second;
            q.pop();
            if (known[u] || w0==INT_MAX) continue; 
            known[u] = 1;
            dist[u] = w0;
            for (const auto& p : G[u]) {
                int v = p.first, w = p.second;
                if (!known[v]) q.push({v, w+w0});
            }
        }
        int res = *max_element(dist.begin()+1, dist.end());
        return res == INT_MAX ? -1 : res;
    }
};