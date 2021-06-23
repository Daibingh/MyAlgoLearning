#include "utils.hpp"

using namespace std;

/*
 给出两个 非空
的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。

如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

示例：

输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807
-------------------------------------------
 * 主要考察 List 的遍历
 * 时间复杂度 O(n), 空间复杂度 O(n)
 * 关键在于如何处理长度不等，可以用“零节点”填充
 * 同时最后一个进位也要注意
 * 结果的开头一般设置“哑节点”
 */

class Solution {
   public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode(0);
        ListNode* curr = head;
        int carry = 0;
        ListNode zero(0);
        while (l1 || l2 || carry) {
            l1 = l1 ? l1 : &zero;
            l2 = l2 ? l2 : &zero;
            int sum = l1->val + l2->val + carry;
            carry = sum / 10;
            curr->next = new ListNode(sum % 10);
            curr = curr->next;
            l1 = l1->next;
            l2 = l2->next;
        }
        return head->next;
    }
};

int main() {
    ListNode* l1 = new ListNode(0);
    add_list_node(l1, {4, 6, 8});
    ListNode* l2 = new ListNode(0);
    add_list_node(l2, {2, 7, 3});
    auto res = Solution().addTwoNumbers(l1->next, l2->next);

    print_list(l1->next);
    print_list(l2->next);

    print_list(res);
}