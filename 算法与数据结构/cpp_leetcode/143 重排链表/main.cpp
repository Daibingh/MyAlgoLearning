#include <bits/stdc++.h>

using namespace std;

/*
给定一个单链表 L：L0→L1→…→Ln-1→Ln ，
将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→…

你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

示例：
给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3.
*/

// 借助数组
class Solution2 {
public:
    void reorderList(ListNode* head) {
        if (!head) return ;
        int n = 0;
        ListNode* cur = head;
        while (cur) {
            ++n;
            cur = cur->next;
        }
        vector<ListNode*> a(n);
        cur = head;
        for (auto & t : a) {
            t = cur;
            cur = cur->next;
        }
        int l = 0, r = n-1;       
        while (l<r) {
            a[l]->next = a[r];
            a[r]->next = a[l+1];
            ++l, --r;
        }
        a[l]->next = nullptr;
    }
};


// 找中点，断开，翻转，合并
class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head) return ;
        ListNode* p1=head, *p2=head->next;
        while (p2 && p2->next) {
            p1 = p1->next;
            p2 = p2->next->next;
        }
        p2 = reverse(p1->next);
        p1->next = nullptr;
        p1 = head;
        ListNode dummy(0), *cur = &dummy;
        while (p1 && p2) {
            cur->next = p1;
            p1 = p1->next;
            cur = cur->next;
            cur->next = p2;
            p2 = p2->next;
            cur = cur->next;
        }
        if (p1) cur->next = p1;
        if (p2) cur->next = p2;
    }

    ListNode* reverse(ListNode* head) {
        ListNode* cur = head;
        ListNode* pre = nullptr;
        while (cur) {
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }
};