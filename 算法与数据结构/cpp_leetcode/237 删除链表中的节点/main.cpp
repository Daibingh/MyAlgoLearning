#include "utils.hpp"
using namespace std;

/*
请编写一个函数，使其可以删除某个链表中给定的（非末尾）节点。传入函数的唯一参数为 要被删除的节点 。

*/

// 通过拷贝下一个元素实现删除节点
class Solution {
public:
    void deleteNode(ListNode* node) {
        node->val = node->next->val;
        ListNode* tmp = node->next;  // optional
        node->next = node->next->next;
        delete tmp;  // optional
    }
};