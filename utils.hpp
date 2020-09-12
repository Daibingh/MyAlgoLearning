#include "bits/stdc++.h"


struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

template<typename T1, typename T2>
void print_dict(std::unordered_map<T1,T2>& m) {
    for (auto & i : m) {
        std::cout<<i.first<<": "<<i.second<<" ";
    }
    std::cout<<std::endl;
}

template<typename T>
void print_vec(const std::vector<T>& v) {
    for (auto& t: v) {
        std::cout<<t<<" ";
    }
    std::cout<<std::endl;
}

template<typename T>
void print_arr(T* p, int n) {
    for (size_t i=0;i<n;++i) {
        std::cout<<*p++<<" ";
    }
    std::cout<<std::endl;
}

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

void print_list(ListNode* l) {
    while (l) {
        std::cout<<l->val<<"->";
        l = l->next;
    }
    std::cout<<"\b\b"<<"  "<<std::endl;
}

void add_list_node(ListNode* l, const std::vector<int>& v) {
    for (auto& t: v) {
        l->next = new ListNode(t);
        l = l->next;
    }
}