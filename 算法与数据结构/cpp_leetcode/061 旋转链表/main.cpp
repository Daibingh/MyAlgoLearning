
#include "utils.hpp"
using namespace std;


/*
给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。

示例 1:

输入: 1->2->3->4->5->NULL, k = 2
输出: 4->5->1->2->3->NULL
解释:
向右旋转 1 步: 5->1->2->3->4->NULL
向右旋转 2 步: 4->5->1->2->3->NULL
---------------------------------
解法：
- 找规律，头尾相接成环，循环移位

*/


class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head) return nullptr; 
        int cnt = 1;
        ListNode* cur = head;
        while (cur->next) {
            cur = cur->next;
            ++cnt;
        }
        k %= cnt;
        k = cnt-k;  // 应该向右循环移动的步数 
        cur->next = head;
        cur = head;
        for (int i=0;i<k;++i) cur = cur->next;
        head = cur;  // 头定位了
        for (int i=0;i<cnt-1;++i) cur = cur->next;
        cur->next = nullptr;   // 尾部断开
        return head;
    }
};