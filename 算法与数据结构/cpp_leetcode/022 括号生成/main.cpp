#include "utils.hpp"

using namespace std;

/*数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。*/



// 生成括号首先要知道什么叫合法的括号
// 合法的括号满足的条件：
// (1) count('(') >= count(')')  0<=i<n-1
// (2) count('(') = count(')')  i=n-1
// 回溯法 生成括号

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        backTracking(res, n);
        return res;
    }

    void backTracking(vector<string>& res, int n, string str="", int left=0, int right=0) {
        if (str.size()==2*n)  // 满足长度要求
            res.push_back(str);
        if (left<n)  // 限制左括号数量
            backTracking(res, n, str+"(", left+1, right);
        if (right<left) // 保证前缀合法
            backTracking(res, n, str+")", left, right+1);
    }
};


////////////////////////////////////////////////////////
// 另一种 写法
class Solution2 {
    vector<string> res;
public:
    vector<string> generateParenthesis(int n) {
        string path;
        helper(path, n, 0, 0);
        return res;
    }

    void helper(string path, int n, int left, int right) {
        if (left<right || left>n) return;
        if (n==left && n==right) {
            res.push_back(path);
            return;
        }
        helper(path+"(", n, left+1, right);
        helper(path+")", n, left, right+1);
    }
};