#include "utils.hpp"

using namespace std;

/*
给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。

说明：不允许修改给定的链表。
*/

// 解法 1：哈希表
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        unordered_set<ListNode*> S;
        ListNode* cur = head;
        while (cur) {
            if (S.find(cur)==S.end()) {
                S.insert(cur);
            }
            else return cur;
            cur = cur->next;
        }
        
        return nullptr;
    }
};


// 解法 2：一种巧妙的双指针解法，占用常数空间
class Solution2 {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next) return nullptr;
        ListNode* f = head->next->next;  // 注意起点，与链表排序不同！！
        ListNode* s = head->next;
        while (f && f->next && f!=s) {
            f = f->next->next;
            s = s->next;       
        }
        if (f!=s) return nullptr;
        s = head;
        while (f!=s) {
            s = s->next;
            f = f->next;
            // cout<<f->val<<", "<<s->val<<endl;
        }
        return s;
    }
};