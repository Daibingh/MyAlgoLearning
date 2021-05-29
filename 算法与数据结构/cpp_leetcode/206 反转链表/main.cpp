
#include "utils.hpp"


// 递归
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode* node  = head->next;
        ListNode* ret =  reverseList(node);
        node->next = head;
        head->next = nullptr;  // 注意这里！
        return ret ;
    }
};

// 循环
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* cur = head;
        while (cur) {
            ListNode* tmp = cur->next;
            cur->next =prev;
            prev = cur;
            cur = tmp;
        }
        return prev;
    }
};