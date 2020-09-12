#include <bits/stdc++.h>



/********************** 实现双向链表 **************************/

// 双向链表的删除可以直接在当前位置，而单向链表必须从从前一个位置考虑

class DoubleList
{
private:
    /* data */

    struct ListNode
    {
        ListNode* next, * prev;
        int val;
        ListNode(int v): val(v), next(nullptr), prev(nullptr) {}
    };

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    void insertAfter(ListNode* prevNode, ListNode* newNode) {
        newNode->next = prevNode->next;
        prevNode->next = newNode;
        newNode->prev = prevNode;
        newNode->next->prev = newNode;
        ++cnt;
    }

     // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    void insertBefore(ListNode* lastNode, ListNode* newNode) {
        newNode->prev = lastNode->prev;
        lastNode->prev = newNode;
        newNode->next = lastNode;
        newNode->prev->next = newNode;
        ++cnt;
    }

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 删除 cur 节点
    ListNode* erase_(ListNode* cur) {
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        ListNode* tmp = cur->next;
        delete cur;
        --cnt;
        return tmp;
    }

    ListNode* loc(int idx) const {  // 根据索引定位前一个，下标从 0 开始
        ListNode* prev = head;
        for (int i=0;i<idx;++i) prev = prev->next;
        return prev;
    }

    ListNode* head, * tail;  // 哑节点
    int cnt;  // 有效节点个数
    

public:
    DoubleList(/* args */);
    ~DoubleList();
    bool empty() const;
    int size() const;
    int & front();
    int & back();
    void push_front(int val);
    void pop_front();
    void push_back(int val);
    void pop_back();
    void insert(int idx, int val);
    void erase(int idx);
    void clear();
    void remove(int val);
    // void sort();
    int & at(int idx);
    void reverse();
    void print() const;
};

DoubleList::DoubleList() {
    head = new ListNode(0);
    tail = new ListNode(0);
    head->next = tail;
    tail->prev = head;
    cnt = 0;
}


DoubleList::~DoubleList() {
    clear();
    delete head;
    delete tail;
}

void DoubleList::clear() {
    ListNode* cur = head->next;
    while (cur!=tail) {
        ListNode* tmp = cur->next;
        delete cur;
        cur = tmp;
    }
    head->next = tail;
    tail->prev = head;
    cnt = 0;
}

int DoubleList::size() const {
    return cnt;
}

bool DoubleList::empty() const {
    return cnt==0;
}

void DoubleList::insert(int idx, int val) {
    assert (idx >=0 and idx <= cnt);
    ListNode* prev = loc(idx);   // 定位 idx 位置前一个
    insertAfter(prev, new ListNode(val));
}

void DoubleList::erase(int idx) {
    assert (idx >=0 and idx < cnt);
    ListNode* node = loc(idx+1);  // 定位 idx 位置
    erase_(node);
}

void DoubleList::push_front(int val) {
    insertAfter(head, new ListNode(val));
}

void DoubleList::pop_front() {
    assert (cnt>0);
    erase_(head->next);
}

void DoubleList::push_back(int val) {
    insertBefore(tail, new ListNode(val));
}

void DoubleList::pop_back() {
    assert (cnt>0);
    erase_(tail->prev);
}

int & DoubleList::front() {
    assert (cnt > 0);
    return head->next->val;
}

int & DoubleList::back() {
    assert (cnt > 0);
    return tail->prev->val;
}

int & DoubleList::at(int idx) {
    assert (idx>=0 && idx < cnt);
    return loc(idx+1)->val;
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void DoubleList::reverse() {
    ListNode* cur = head;
    while (cur) {
        ListNode* tmp = cur->next;
        cur->next = cur->prev;
        cur->prev = tmp;
        cur = tmp;
    }
    ListNode* tmp = head;
    head = tail;
    tail = tmp;
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void DoubleList::remove(int val) {
    ListNode* cur = head->next;
    while (cur!=tail) {
        if (cur->val==val) {
           cur = erase_(cur); 
        }
        else {
            cur = cur->next;
        }
    }
}

void DoubleList::print() const {
    ListNode* cur = head->next;
    while (cur!=tail) {
        std::cout<<cur->val<<" ";
        cur = cur->next;
    }
    std::cout<<std::endl;
}


int main() {
    DoubleList list;
    for (auto t : std::vector<int>{1,2,3,4,5}) {
        list.push_front(t);
        // list.push_back(t);
    }
    list.print();
    std::cout<<list.size()<<std::endl;
    std::cout<<list.at(3)<<std::endl;
    list.insert(3, 5);
    list.print();
    std::cout<<list.size()<<std::endl;
    std::cout<<list.back()<<", "<<list.front()<<std::endl;
    list.remove(5);
    list.print();
    std::cout<<list.size()<<std::endl;
    list.reverse();
    list.print();
    std::cout<<list.size()<<std::endl;
    list.erase(1);
    list.print();
    std::cout<<list.size()<<std::endl;
    list.clear();
    list.print();
    std::cout<<list.size()<<std::endl;
    
}