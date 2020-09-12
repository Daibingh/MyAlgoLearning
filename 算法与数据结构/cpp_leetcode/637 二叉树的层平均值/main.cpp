#include "utils.hpp"
#include <bits/stdc++.h>

using namespace std;


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<pair<long long, int>> sum_cnt;
        preorder(root, sum_cnt, 0);
        vector<double> res;
        for (const auto& p : sum_cnt) {
            res.push_back(static_cast<double>(p.first) / p.second);
        }
        return res;
    }
    
    void preorder(TreeNode* root, vector<pair<long long, int>>& sum_cnt, int depth) {
        if (!root) return;
        if (sum_cnt.size()<=depth) sum_cnt.push_back({0,0});
        sum_cnt[depth].first += root->val;
        ++sum_cnt[depth].second;
        preorder(root->left, sum_cnt, depth+1);
        preorder(root->right, sum_cnt, depth+1);
    }
};

int main() {

}