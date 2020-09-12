#include "utils.hpp"

using namespace std;

/*
- 实现前缀树
- https://mp.weixin.qq.com/s/uDar0F7x9w5F3sHOB5tIDA
*/

class Trie {
    
    private:
        bool isEnd;  // 当前节点是否是一个串的结尾
        Trie* next[26];  // 下一个字符
public:
    /** Initialize your data structure here. */
    Trie() {
        isEnd = false;
        std::fill(next, next+26, nullptr);
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie* node = this;
        for (const auto & c: word) {
            if (!node->next[c-'a']) {
                node->next[c-'a'] = new Trie();   // 这里要注意不要先复制指针再 new
            }
            node = node->next[c-'a'];
        }
        node->isEnd = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie* node = this;
        for (const auto & c : word) {
            node = node->next[c-'a'];
            if (!node) return false;
        }
        return node->isEnd;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie* node = this;
        for (const auto & c : prefix) {
            node = node->next[c-'a'];
            if (!node) return false;
        }
        return true;
    }
};

int main() {

}
