#include <bits/stdc++.h>

using namespace std;


/*
给定一个链表，每个节点包含一个额外增加的随机指针，该指针可以指向链表中的任何节点或空节点。

要求返回这个链表的 深拷贝。 

我们用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：

val：一个表示 Node.val 的整数。
random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。

*/


// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};


class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> old2new;
        Node* cur1=head;
        while (cur1) {
            old2new[cur1] = new Node(cur1->val);  // 不用连接，只创建节点并建立对应关系
            cur1 = cur1->next;
        }
        cur1 = head;
        while (cur1) {  // 根据对应关系建立连接
            old2new[cur1]->next = old2new[ cur1->next ];
            old2new[cur1]->random = old2new[ cur1->random ];
            cur1 = cur1->next;
        }
        return old2new[head];
    }
};