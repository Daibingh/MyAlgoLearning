#include <bits/stdc++.h>
using namespace std;

/*
给定一个单链表，把所有的奇数节点和偶数节点分别排在一起。请注意，这里的奇数节点和偶数节点指的是节点编号的奇偶性，而不是节点的值的奇偶性。

请尝试使用原地算法完成。你的算法的空间复杂度应为 O(1)，时间复杂度应为 O(nodes)，nodes 为节点总数。

示例 1:

输入: 1->2->3->4->5->NULL
输出: 1->3->5->2->4->NULL

*/

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head) return nullptr;
        ListNode* head1 = head, *head2 = head->next;
        ListNode* cur1 = head1, *cur2 = head2;

        while (cur2 && cur2->next) {
            cur1->next = cur2->next;
            cur1 = cur1->next;
            cur2->next = cur1->next;
            cur2 = cur2->next;
        }
        cur1->next = head2;
        return head1;
    }
};
