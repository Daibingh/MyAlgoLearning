#include "utils.hpp"

using namespace std;

/*
请判断一个链表是否为回文链表。

*/


// O(1) 常数空间
// 快慢指针找中点，翻转后半部分，进行比较
class Solution {

    ListNode* reverse(ListNode* s) {
        ListNode* pre = nullptr;
        while (s) {
            ListNode* tmp = s->next;
            s->next = pre;
            pre = s;
            s = tmp;
        }
        return pre;
    }

public:
    bool isPalindrome(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;  
        }  // 退出后，slow 指向中间（奇数链表） 或下一半的开始（偶数链表）
        ListNode* head2 = reverse(slow);  // 翻转下一半链表
        while (head2 && head) {  // 两个链表从头到尾比较，不用管多出来的节点，奇偶不影响
            if (head->val != head2->val)
                return false;
            head = head->next;
            head2 = head2->next;
        }
        return true;
    }
};