#include "utils.hpp"
using namespace std;

/*
给定一个二维网格 board 和一个字典中的单词列表 words，找出所有同时在二维网格和字典中出现的单词。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母在一个单词中不允许被重复使用。
*/

// 时间复杂度？
// 分别对每个 word 进行回溯
class Solution {
    int m,n;
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> res;
        m = board.size();
        n = board[0].size();
        for (auto & w : words) {
            if (helper(board, w)) res.push_back(w);
        }
        return res;
    }

    // 从某个点为起点开始遍历
    bool helper(vector<vector<char>>& board, string& word) {
        for (int i=0;i<m;++i) {
            for (int j=0;j<n;++j) {
                if ( findWords(board, word, i, j, 0) ) return true;
                
            }
        }
        return false;
    }
    
    // 递归函数
    bool findWords(vector<vector<char>>& board, string& word, int y, int x, int depth) {
        if (y<0 || y>=m || x<0 || x>=n || board[y][x]=='#' || board[y][x]!=word[depth]) return false;
        if (depth+1 == word.size()) return true;
        char ch = board[y][x];
        board[y][x] = '#';
        bool ret = findWords(board, word, y+1, x, depth+1)
            || findWords(board, word, y, x+1, depth+1)
            || findWords(board, word, y, x-1, depth+1)
            || findWords(board, word, y-1, x, depth+1);
        board[y][x] = ch;
        return ret;
    }
};


// 使用前缀树的回溯 
// 64 ms, 在所有 C++ 提交中击败了 84.03% 的用户
class Solution2 {

    struct Trie {
        vector<Trie*> next;
        string str;

        Trie():next(vector<Trie*>(26, nullptr)) {}
    };

    int m,n;

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> res;
        m = board.size();
        n = board[0].size();

        Trie* root = new Trie();
        for (auto & w : words) {
            insert(root, w);
        }

        for (int i=0;i<m;++i) {
            for (int j=0;j<n;++j) {
                dfs(res, board, root, i, j);
            }
        }
        return res;
    }

    void dfs(vector<string>& res, vector<vector<char>>& board, Trie* root, int y, int x) {
        if (y<0 || y>=m || x<0 || x>=n) return;
        char ch = board[y][x];
        if ( ch=='#' || ! root->next[ch-'a'] ) return;
        Trie* next = root->next[ch-'a'];
        if ( ! next->str.empty() ) {
            res.push_back(next->str);
            next->str = "";
        }
        board[y][x] = '#';
        dfs(res, board, next, y+1, x);
        dfs(res, board, next, y, x+1);
        dfs(res, board, next, y, x-1);
        dfs(res, board, next, y-1, x);
        board[y][x] = ch;
    }

    void insert(Trie* root, string & word) {
        for (auto & c : word) {
            if (!root->next[c-'a']) root->next[c-'a'] = new Trie();
            root = root->next[c-'a'];
        }
        root->str = word;
    }
};