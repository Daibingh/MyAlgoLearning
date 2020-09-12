#include "../utils.hpp"

using namespace std;


class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        int len = 0;
        string s = strs[0];
        for (int i=0;i<s.size();++i) {
            bool f = false;
            for (int j=1;j<strs.size();++j) {
                if (i<strs[j].size() && s[i]==strs[j][i]) continue;
                else {
                    f = true;
                    break;
                }
            }
            if (f) break;
            else ++len;
        }
        return s.substr(0,len);
    }
};


////////////////////////////////////////////////////////////////
// 前缀树
struct Node {
    vector<Node*> next;
    bool isEnd;

    Node():next(vector<Node*>(26, nullptr)), isEnd(false) {}
};

class Solution2 {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";  // 处理两种特殊情况
        if (strs.size()==1) return strs[0];
        Node root;
        insert(&root, strs.front());
        string res;
        for (int i=1;i<strs.size();++i) {
            res = travel(&root, strs[i]);
        }
        return res;
    }

    void insert(Node* root, string& str) {
        for (const auto & c : str) {
            if (!root->next[c-'a']) 
                root->next[c-'a'] = new Node;
            root = root->next[c-'a'];
        }
        root->isEnd = true;
    }

    string travel(Node* root, string& str) {
        string ret;
        for (int i=0;i<str.size();++i) {
            if (root->isEnd || !root->next[str[i]-'a'] ) break;  // 如果遇到某个字符串的结尾，或者出现新字符时，停止遍历
            ret += str[i];
            root = root->next[str[i]-'a'];
        }
        root->isEnd = true;
        return ret;
    }
};