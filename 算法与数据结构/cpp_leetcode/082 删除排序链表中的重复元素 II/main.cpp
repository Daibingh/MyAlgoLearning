#include <bits/stdc++.h>

using namespace std;

/*
给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中 没有重复出现 的数字。
示例 1:

输入: 1->2->3->3->4->4->5
输出: 1->2->5
*/

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode dummy(0), *prev=&dummy;
        prev->next = head;
        ListNode* curr = head;
        while (curr) {
            if (!curr->next || curr->val != curr->next->val ) prev = curr;
            else {
                while (curr->next && curr->val == curr->next->val) curr = curr->next;
                prev->next = curr->next;
            }
            curr = prev->next;
        }
        return dummy.next;
    }
};

/* 
凡是有可能删除头的情况，都要用到哑节点
*/