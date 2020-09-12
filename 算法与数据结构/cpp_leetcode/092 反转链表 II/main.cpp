
#include "utils.hpp"

using namespace std;


class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* p1 = dummy;
        for (int i=1;i<m;++i) p1=p1->next;  // 注意下标从 1 开始
        ListNode* ppre = p1;  // 翻转部分的前一个节点
        p1 = p1->next;  // 翻转开始
        ListNode* p2 = p1;
        for (int i=m;i<n;++i) p2=p2->next;  // p2 翻转结束
        ListNode* cur = p1;    // 当前要翻转的
        ListNode* pre = p2->next;  // 当前的前一个
        while (pre!=p2) {  // 开始局部翻转
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        ppre->next = p2;  // 连接头部
        return dummy->next;
    }
};

