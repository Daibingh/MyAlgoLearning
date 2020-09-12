#include "utils.hpp"

using namespace std;

/*
给出方程式 A / B = k, 其中 A 和 B 均为用字符串表示的变量， k 是一个浮点型数字。根据已知方程式求解问题，并返回计算结果。如果结果不存在，则返回 -1.0。

示例 :
给定 a / b = 2.0, b / c = 3.0
问题: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? 
返回 [6.0, 0.5, -1.0, 1.0, -1.0 ]
*/


// DFS
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equ, 
                                vector<double>& val, 
                                vector<vector<string>>& que) 
        {
        // 建图
        unordered_map<string, vector<pair<string, double>>> graph;
        for (int i=0;i<equ.size();++i) {
            graph[equ[i][0]].emplace_back(equ[i][1], val[i]);
            graph[equ[i][1]].emplace_back(equ[i][0], 1./val[i]);
        }
        unordered_map<string, bool> vis;
        vector<double> res;
        for ( auto & t : que) {
            if (graph.count(t[0]) && graph.count(t[1]))
                res.push_back( dfs( graph, vis,  t[0], t[1] ) );
            else 
                res.push_back( -1. );
        }
        return res;
    }

    // 有返回值的 DFS
    double dfs(unordered_map<string, 
                vector<pair<string, double>>>& graph, 
                unordered_map<string, bool>& vis,
                string& start,
                string& end ) 
    {
        if (start==end) {
            return 1;
        }
        vis[start] = true;
        bool f = false;
        double ret = 0;
        for (auto & t: graph[start]) {
            if (vis[t.first]) continue;
            double rec = dfs(graph, vis, t.first, end);  // 递归的结果
            if (rec==-1) continue;
            ret = t.second * rec;
            f = true;
        }
        vis[start] = false;
        if (!f) return -1;  // 无路可走返回 -1
        return ret;
    }
};