#include <bits/stdc++.h>
#include "utils.hpp"

using namespace std;

/*
考察 DFS 或 树的遍历, backtracking 
类似题目：求解数独
与求解数独不同的是，backtracking 不需要返回 bool, 求解数独只需要找到一个解，该题是求全部解
*/

class Solution {

    vector<vector<string>> res;  // 结果集
    vector<string> cur;  // 当前解状态
    int n;

public:
    vector<vector<string>> solveNQueens(int n) {
        this->n = n;
        cur = vector<string>(n, string(n, '.'));
        backTracking();
        return res;
    }

    void backTracking(int row=0) {
        if (row==n) {
            res.push_back(cur);
            return;
        }
        for (int i=0;i<n;++i) {
            if (isValid(row, i)) {
                cur[row][i] = 'Q';
                backTracking(row+1);
                cur[row][i] = '.';
            }
        }
    }

    bool isValid(int row, int col) {
        for (int i=0;i<n;++i) {
            if (cur[row][i]=='Q') return false;
            if (cur[i][col]=='Q') return false;
        }
        int r=row,c=col;
        for (;r>=0 && c>=0; --r, --c) {
            if (cur[r][c]=='Q') return false;
        }
        r=row;
        c=col;
        for (;r>=0 && c<n;--r,++c) {
            if (cur[r][c]=='Q') return false;
        }
        return true;
    }

};

int main() {
    auto res = Solution().solveNQueens(8);
    cout<<res.size()<<endl;
    for (auto& v: res) {
        for (auto& s: v) {
            cout<<s<<endl;
        }
        cout<<"---------------"<<endl;
    }
}