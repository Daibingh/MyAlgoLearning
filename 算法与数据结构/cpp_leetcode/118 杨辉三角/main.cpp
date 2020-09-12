#include "utils.hpp"
using namespace std;

/*
给定一个非负整数 numRows，生成杨辉三角的前 numRows 行。

*/

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        if (numRows<1) return {};
        vector<vector<int>> res;
        res.push_back({1});
        for (int i=1;i<numRows;++i) {
            const auto & last = res.back();  // 获取上一行
            vector<int> tmp(i+1, 1);  // 初始化当前行全1
            for(int j=1;j<i;++j) {
                tmp[j] = last[j-1] + last[j];
            }
            res.push_back(tmp);
        }
        return res;
    }
};
