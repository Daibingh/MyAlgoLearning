#include <bits/stdc++.h>
#include "utils.hpp"

using namespace std;


/*
班上有 N 名学生。其中有些人是朋友，有些则不是。他们的友谊具有是传递性。如果已知 A 是 B 的朋友，B 是 C 的朋友，那么我们可以认为 A 也是 C 的朋友。所谓的朋友圈，是指所有朋友的集合。

给定一个 N * N 的矩阵 M，表示班级中学生之间的朋友关系。如果M[i][j] = 1，表示已知第 i 个和 j 个学生互为朋友关系，否则为不知道。你必须输出所有学生中的已知的朋友圈总数。

*/


// 每个人为节点

// dfs 递归
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        int res = 0;
        vector<int> vis(n, false);
        for (int i=0;i<n;++i) {
            if (vis[i]) continue;
            dfs(M, vis, i);
            res += 1;  // 没访问过的人一定有一个新的朋友圈
        }
        return res;
    }
    
    void dfs(vector<vector<int>>& M, vector<int>& vis, int i) {
        for (int j=0;j<M.size();++j) {  // 检查 i 与每个人的联系，dfs（包括自己）
            if (vis[j] || !M[i][j]) continue;
            vis[i] = true;
            dfs(M, vis, j);
        }
    }
};


// bfs
class Solution2 {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        int res = 0;
        vector<int> vis(n, false);
        queue<int> que;
        for (int i=0;i<n;++i) {
            if (vis[i]) continue;
            que.push(i);
            while (!que.empty()) {
                int k = que.front();
                que.pop();
                vis[k] = true;
                for (int j=0;j<n;++j) {
                    if (!M[k][j] || vis[j]) continue;
                    que.push(j);
                }
            }
            ++res;
        }
        return res;
    }
    
};


// 并查集解法，动态连通性
class UF {
    
public:
    vector<int> parent;
    vector<int> size;
    int cnt;
    
    
    UF(int n) {
        parent = vector<int>(n);
        size = vector<int>(n,1);
        cnt = n;
        for (int i=0;i<n;++i) parent[i] = i;  // 初始化 parent 为自己
    }
    
    // 查询 x 的根，同时作路径压缩
    int find(int x) {
        while (parent[x]!=x) {
            parent[x] = parent[ parent[x] ];  // 将 x 提升到它 爷爷 下面
            x = parent[x];
        }
        return x;
    }
    
    
    void union_(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx==ry) return;
        
        if (size[rx]<size[ry]) {
            parent[rx] = ry;  // 注意这里不是 直接吧 x 挂到 ry 上，而是 rx -> ry
            size[ry] += size[rx];
        }
        else {
            parent[ry] = rx;
            size[rx] += size[ry];
        }
        --cnt;  // 每次合并一个，联通分量个数减一
    }
    
};



class Solution3 {
public:
    int findCircleNum(vector<vector<int>>& M) {
        UF u(M.size());
        for (int i=0;i<M.size();++i) {
            for (int j=0;j<i;++j) {
                if (M[i][j]) u.union_(i,j);
            }
        }
        return u.cnt;
    }
};