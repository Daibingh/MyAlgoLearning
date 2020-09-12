#include "utils.hpp"

using namespace std;


/*合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。*/

/*
解法：
- 两两合并 O(k^2*n)
- 分治合并 O(kn*log(k))
- 优先队列 O(kn*log(k))
*/

class Solution {
public:
    struct Status {
        int val;
        ListNode *ptr;
        bool operator < (const Status &rhs) const {
            return val > rhs.val;  // 小顶堆
        }
    };

ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<Status> q;
    for (auto l : lists) {
        if (l) q.push({l->val, l});
    }
    ListNode dummy(0);
    ListNode* cur = &dummy; 
    while (!q.empty()) {
        auto t = q.top();
        q.pop();
        cur->next = t.ptr;
        cur = cur->next;
        if (t.ptr->next) q.push({t.ptr->next->val, t.ptr->next});
    }
    
    return dummy.next;
    
}
};

/////////////////////////////////////////////////////////////////
// 另一种写法 
struct comp {
    bool operator() (const ListNode* n1, const ListNode* n2) {
        return n1->val > n2->val;
    }
};

class Solution2 {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, comp> q;
        for (auto & t : lists) {
            if (t) q.push(t);
        }
        ListNode head(0), *cur=&head;
        while (!q.empty()) {
            auto t = q.top();
            q.pop();
            cur->next = t;
            cur = cur->next;
            if (t->next) q.push(t->next);
        }
        return head.next;
    }
};

int main() {
    
    ListNode* l1 = new ListNode(0);
    add_list_node(l1, {1,4,5});
    ListNode* l2 = new ListNode(0);
    add_list_node(l2, {1,3,4});
    ListNode* l3 = new ListNode(0);
    add_list_node(l3, {2,6});
    vector<ListNode*> a{l1->next, l2->next, l3->next};
    auto res = Solution().mergeKLists(a);
    print_list(res);
}