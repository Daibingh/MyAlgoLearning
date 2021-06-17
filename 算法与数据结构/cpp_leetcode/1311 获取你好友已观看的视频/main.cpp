#include <bits/stdc++.h>

using namespace std;


// BFS
class Solution {
   public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos,
                                          vector<vector<int>>& friends,
                                          int id,
                                          int level) {
        unordered_map<int, vector<int>> graph;
        int i = 0;
        for (const auto& t : friends) {
            for (const auto& k : t)
                graph[i].push_back(k);
            ++i;
        }
        queue<int> q;
        q.push(id);
        unordered_set<int> visted;
        visted.insert(id);
        while (!q.empty()) {
            if (level == 0)
                break;
            for (int i = q.size(); i > 0; --i) {
                int t = q.front();
                q.pop();
                for (const auto& k : graph[t]) {
                    if (visted.count(k))
                        continue;
                    q.push(k);
                    visted.insert(k);
                }
            }
            --level;
        }

        unordered_map<string, int> videoCnt;
        while (!q.empty()) {
            for (const auto& t : watchedVideos[q.front()])
                ++videoCnt[t];
            q.pop();
        }
        vector<pair<string, int>> vec(videoCnt.begin(), videoCnt.end());
        sort(vec.begin(), vec.end(),
             [](const pair<string, int>& a, const pair<string, int>& b) {
                 return a.second < b.second ||
                        (a.second == b.second && a.first < b.first);
             });

        vector<string> res;
        for (const auto& t : vec)
            res.push_back(t.first);
        return res;
    }
};