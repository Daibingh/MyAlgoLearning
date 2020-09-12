#include "utils.hpp"

using namespace std;

/*
在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。

*/

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        // 找链表的中点，快慢指针法
        ListNode* l = head;  // 慢指针从头开始
        ListNode* r = head->next;  // 快指针从第二个开始（不能也从头开始，否则两个元素的话不能均分）
        while (r && r->next)
        {
            l = l->next;  // 慢指针走一步
            r = r->next->next;  // 快指针走两步，循环结束 mid == r
        }
        ListNode* lhead = head;  // 左侧 [head, mid]
        ListNode* rhead = l->next;  // 右侧 [mid+1, end]
        l->next = nullptr;  // 断开之间的连接
        lhead = sortList(lhead);   // 左侧递归分割
        rhead = sortList(rhead);  // 右侧递归分割
        // 下面合并两个有序链表
        ListNode* dummy = new ListNode(0); 
        ListNode* cur = dummy;
        while (lhead && rhead) {
            if (lhead->val < rhead->val) {
                cur->next = lhead;
                lhead = lhead->next;
            }
            else {
                cur->next = rhead;
                rhead = rhead->next;
            }
            cur = cur->next;
        }
        if (lhead) cur->next = lhead;
        if (rhead) cur->next = rhead;
        return dummy->next;
    }
};