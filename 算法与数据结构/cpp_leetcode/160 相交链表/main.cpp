#include "utils.hpp"

using namespace std;

/* 编写一个程序，找到两个单链表相交的起始节点。 */


// 解法 1：哈希表
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode*> vis;
        ListNode* cur = headA;
        while (cur) {
            vis.insert(cur);
            cur = cur->next;
        }
        cur = headB;
        while (cur && vis.find(cur)==vis.end()) cur = cur->next;
        return cur;
    }
};


// 解法 2：转换为 142 题 环形链表 II
class Solution2 {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return nullptr;
        ListNode* cur = headA;
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = headA;
        auto res = detectCycle(headB);
        cur->next = nullptr;
        return res;
    }
    
    
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next) return nullptr;
        ListNode* f = head->next->next;
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


// 解法 3：对称性 headA->end->headB, headB->end->headA, 相交
class Solution3 {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *a=headA,*b=headB;
        while(a!=b){
            a=a?a->next:headB;  // A 走都头，接着从 B 开始
            b=b?b->next:headA;  // B 走都头，接着从 A 开始
        }
        return a;
    }
};