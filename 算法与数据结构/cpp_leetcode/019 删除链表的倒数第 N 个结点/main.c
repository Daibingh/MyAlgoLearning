#include <stdlib.h>

/*
给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

*/

struct ListNode {
    int val;
    struct ListNode* next;
};

// 解法 1：双指针
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode* first = head;
    struct ListNode* second = head;
    int i = 0;
    for (; first && i < n; ++i) {
        first = first->next;
    }
    if (first == NULL) {
        struct ListNode* next = head->next;
        free(head);
        return next;
    }
    while (first->next) {
        first = first->next;
        second = second->next;
    }
    struct ListNode* tmp = second->next;
    second->next = second->next->next;
    free(tmp);
    return head;
}

// 解法 2：递归
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    static int cur = 0;
    if (!head)
        return NULL;
    head->next = removeNthFromEnd(head->next, n);
    return ++cur == n ? head->next : head;  // 回溯时 ++cur 与 n 比较
}