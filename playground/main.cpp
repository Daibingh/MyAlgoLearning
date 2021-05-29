
// freopen("playground/data.in", "r", stdin);

// #include <ctype.h>
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <math.h>
#include <bits/stdc++.h>

using namespace std;

void print_graph(const unordered_map<int, vector<int>>& graph) {
    for (const auto& t : graph) {
        cout << t.first << ": ";
        for (const auto& k : t.second) {
            cout << k << " ";
        }
        cout << endl;
    }
}

void dfs(const unordered_map<int, vector<int>>& graph,
         unordered_set<int>& visted,
         int start) {
    if (visted.count(start))
        return;
    visted.insert(start);
    const auto t = graph.find(start);
    if (t == graph.end())
        return;
    for (const auto& v : t->second) {
        dfs(graph, visted, v);
    }
}

int main() {
    freopen("playground/data.in", "r", stdin);

    unordered_map<int, vector<int>> graph;

    string line;
    while (getline(cin, line)) {
        // cout<<line<<endl;
        stringstream ss(line);
        int u = 0, v = 0;
        ss >> u;
        while (ss >> v) {
            graph[u].push_back(v);
        }
    }

    // print_graph(graph);

    unordered_set<int> visted;

    dfs(graph, visted, 0);

    for (const auto& u : visted) {
        cout << u << endl;
    }
}