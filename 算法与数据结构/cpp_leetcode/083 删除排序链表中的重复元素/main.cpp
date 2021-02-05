#include <bits/stdc++.h>

using namespace std;

/*
给定一个**排序链表**，删除所有重复的元素，使得每个元素只出现一次。
*/

// 双指针
class Solution2 {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* p1 = head, * p2 = head;
        while (p1) {
            while (p2 && p1->val==p2->val) {
                p2 = p2->next;
            }
            p1->next = p2;
            p1 = p2;
        }
        return head;
    }
};


// 递归
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) return head;
        head->next = deleteDuplicates(head->next);
        if (head->val == head->next->val) head = head->next;
        return head;
    }
};
