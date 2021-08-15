
// freopen("playground/data.in", "r", stdin);

#include <bits/stdc++.h>
#include "utils.hpp"

using namespace std;

class Solution {
    set<int> vis;
public:
    vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
        travel(root);
        vector<int> arr(vis.begin(), vis.end());
        vector<vector<int>> res;
        for (const auto & t : queries) {
            auto it = lower_bound(arr.begin(), arr.end(), t);
            if (it == arr.end()) {
                res.push_back({arr.back(), -1});
                continue;
            }
            int idx = distance(arr.begin(), it);
            if (arr[idx] == t) {
                res.push_back({t, t});
            } else if (it == arr.begin()) {
                res.push_back({-1, arr[0]});
            } else {
                res.push_back({arr[idx-1], arr[idx]});
            }
        }
        return res;
    }

    void travel(TreeNode* root) {
        if (!root) {
            return;
        }
        vis.insert(root->val);
        travel(root->left);
        travel(root->right);
    }
};

int main() {
    vector<int> a{4,4,2,4,3};

    int sum = accumulate(a.begin(), a.begin()+2, 0);

}