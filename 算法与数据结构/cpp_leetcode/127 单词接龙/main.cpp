#include "utils.hpp"
using namespace std;

/*
给定两个单词（beginWord 和 endWord）和一个字典，找到从 beginWord 到 endWord 的最短转换序列的长度。转换需遵循如下规则：

每次转换只能改变一个字母。
转换过程中的中间单词必须是字典中的单词。
说明:

如果不存在这样的转换序列，返回 0。
所有单词具有相同的长度。
所有单词只由小写字母组成。
字典中不存在重复的单词。
你可以假设 beginWord 和 endWord 是非空的，且二者不相同。
示例 1:

输入:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

输出: 5
------------------------------------------------
- 无权图两点之间最短路径：BFS

*/


// Author: Huahua
// Running time: 93 ms
// 单向 BFS
class Solution2 {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (!dict.count(endWord)) return 0;  // endWord 必须在字典中
        
        queue<string> q;
        q.push(beginWord);
        
        int l = beginWord.length();
        int step = 0;
        
        while (!q.empty()) {
            ++step;
            for (int size = q.size(); size > 0; size--) {   // 逐层遍历   
                string w = q.front();                
                q.pop();
                for (int i = 0; i < l; i++) {                
                    char ch = w[i];
                    for (int j = 'a'; j <= 'z'; j++) {
                        w[i] = j;
                        // Found the solution
                        if (w == endWord) return step + 1;
                        // Not in dict, skip it
                        if (!dict.count(w)) continue;
                        // Remove new word from dict
                        dict.erase(w);
                        // Add new word into queue
                        q.push(w);                    
                    }
                    w[i] = ch;
                }
            }
        }
        return 0;
    }
};


// Author: Huahua
// Running time: 32 ms (better than 96.6%)
// 双向 BFS
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());        
        if (!dict.count(endWord)) return 0;
        
        int l = beginWord.length();
        
        unordered_set<string> q1{beginWord};  // 这里不用队列，因为需要在队列中查找
        unordered_set<string> q2{endWord};
                
        int step = 0;
        
        while (!q1.empty() && !q2.empty()) {
            ++step;
            
            // Always expend the smaller queue first
            if (q1.size() > q2.size())  //选择较小的一端 往下遍历，平衡作用
                std::swap(q1, q2);
                        
            unordered_set<string> q;  // 临时的 q 用于存 q1 的下一层 “node”， 上层与下层分开存放，因为 set 无序，不满足FIFO
            
            for (string w : q1) {
                for (int i = 0; i < l; i++) {
                    char ch = w[i];
                    for (int j = 'a'; j <= 'z'; j++) {
                        w[i] = j;
                        if (q2.count(w)) return step + 1;  // q1的下一层 出现在 q2 中，说明两头接上来
                        if (!dict.count(w)) continue;                        
                        dict.erase(w);
                        q.insert(w);
                    }
                    w[i] = ch;
                }
            }
            
            std::swap(q, q1);  // 下一层 赋给当前层
        }
        
        return 0;
    }
};