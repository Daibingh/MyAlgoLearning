#include <bits/stdc++.h>

using namespace std;

/*
给你两个 非空 链表来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。

你可以假设除了数字 0 之外，这两个数字都不会以零开头。

*/

// 递归
// 其它解法：翻转链表；使用 stack
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int n1 = get_count(l1);
        int n2 = get_count(l2);
        if (n1<n2) {
            swap(l1, l2);
            swap(n1, n2);
        }
        auto p = helper(l1, l2, n1, n2);
        if (p->val>9) {
            p->val %= 10;
            ListNode* p2 = new ListNode(1);
            p2->next = p;
            return p2;
        }
        return p;
    }

    ListNode* helper(ListNode* l1, ListNode* l2, int k1, int k2) {
        if (!l1) return nullptr;
        int val;
        ListNode* next;
        if (k1==k2) {
            next = helper(l1->next, l2->next, k1, k2);
            val = l1->val + l2->val;
        }
        else {
            next = helper(l1->next, l2, k1-1, k2);
            val = l1->val;
        }
        
        if (next) {
            val += next->val / 10;
            next->val %= 10;
        }
        ListNode * node = new ListNode(val);
        node->next = next;
        return node;
    }

    int get_count(ListNode* p) {
        if (!p) return 0;
        return get_count(p->next) + 1;
    }
};