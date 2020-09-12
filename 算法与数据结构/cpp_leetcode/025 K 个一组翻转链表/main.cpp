#include "utils.hpp"
#include <bits/stdc++.h>

using namespace std;

/*
给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。
算法：
- 转化为多个子链的翻转，先内部翻转，然后外部在调整对接

*/



// struct ListNode {
//     int val;
//     ListNode *next;
//     ListNode(int x) : val(x), next(nullptr) {}
// };


class Solution {
public:
    // 翻转整个链表
    ListNode* reverse(ListNode* head) {

        ListNode* cur = head;
        ListNode* pre = nullptr;
        while (cur) {
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }

    // 递归翻转
    ListNode* reverseRecurrence(ListNode* head) {
         if (!head || !head->next) return head;
         ListNode* p = reverseList(head->next);
         head->next->next = head;
         head->next = nullptr;
         return p;
    }

    // 翻转子链表 [head, tail]
    pair<ListNode*, ListNode*> reverseSub(ListNode* head, ListNode* tail) {
        ListNode* cur = head;
        ListNode* pre = nullptr;  // pre 是 cur 的前一个节点
        while (pre!=tail) {
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        return {tail, head};
    }
    
    // K 组翻转
     ListNode* reverseKGroup(ListNode* head, int k) {

        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* pre = dummy;
        
        while (head) {
            ListNode* tail = head;  // 更新 子链末尾节点
            int cnt = 1;
            while (cnt < k && tail) {  // 定位下一个子链
                tail = tail->next;
                ++cnt;
            }
            if (!tail) {  // 如果最后一个子链长度不足 k 不用 翻转，直接返回 head
                return dummy->next; 
            }

            ListNode* newHead = tail->next;  // 保护子链后面的一个节点
            std::tie(head, tail) = reverseSub(head, tail);  // 翻转子链

            pre->next = head;  // 子链之前的节点对接
            tail->next = newHead;  // 子链后面的节点对接

            pre = tail;  // 更新 子链之前的节点
            head = newHead;  // 更新 子链开始节点

        }
        
        return dummy->next;
        
    }

};

// 递归解法，简洁
class Solution2 {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k<2) return head;
        int cnt = 0;
        ListNode* cur = head;
        while (cur && cnt<k) {
            cur = cur->next;
            ++cnt;
        }
        if (cnt<k) return head;  // 长度不足 k，不用继续递归翻转，直接返回 head
        cur = reverseKGroup(cur, k);  // 递归翻转后面的，返回翻转后的 head
        ListNode* tmp;
        while (cnt>0) {
            tmp = head->next;  // 备份下一个
            head->next = cur;  // 指向前一个
            cur = head;  // 更新前一个位置
            head = tmp;  // 更新当前位置
            --cnt;
        }
        return cur;
    }
};


int main() {

    // 创建链表
    vector<int> v{1,2,3,5,8};
    ListNode* dummy = new ListNode(0); // 哑节点，真正的头节点为 dummy->next
    ListNode* cur = dummy;
    for (auto& t: v) {
        cur->next = new ListNode(t);
        cur = cur->next;
    }

    print_list(dummy->next);
    // dummy->next = Solution().reverse(dummy->next);
    dummy->next = Solution().reverseKGroup(dummy->next, 3);
    print_list(dummy->next);

    return 0;
}