#include <bits/stdc++.h>

/********************** 实现单向链表 **************************/

class SingleList
{
private:
    /* data */

    struct ListNode
    {
        ListNode* next;
        int val;
        ListNode(int v): val(v), next(nullptr) {}
    };

    void insert_(ListNode* prev, ListNode* newNode) {
        newNode->next = prev->next;
        prev->next = newNode;
        ++cnt;
    }

    // 删除 prev 的下一个节点
    void erase_(ListNode* prev) {
        ListNode* tmp = prev->next;
        prev->next = prev->next->next;
        delete tmp;
        --cnt;
    }

    ListNode* loc(int idx) const {  // 根据索引定位前一个，下标从 0 开始
        ListNode* prev = dummy;
        for (int i=0;i<idx;++i) prev = prev->next;
        return prev;
    }

    ListNode* dummy;  // 哑节点
    int cnt;  // 有效节点个数
    

public:
    SingleList(/* args */);
    ~SingleList();
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

SingleList::SingleList(): cnt(0), dummy(new ListNode(0)) {}

SingleList::~SingleList()
{
    clear();
    delete dummy; 
}

int SingleList::size() const {
    return cnt;
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void SingleList::clear() {
    ListNode* cur = dummy->next;
    while (cur)
    {
        ListNode* tmp = cur->next;
        delete cur;
        cur = tmp;
    }
    dummy->next = nullptr;
    cnt = 0;
}

bool SingleList::empty() const {
    return cnt == 0;
}

void SingleList::insert(int idx, int val) {
    assert (idx >=0 and idx <= cnt);
    ListNode* prev = loc(idx);   // 定位 idx 位置前一个
    insert_(prev, new ListNode(val));
}

void SingleList::erase(int idx) {
    assert (idx >=0 and idx < cnt);
    ListNode* prev = loc(idx);  // 定位 idx 位置前一个
    erase_(prev);
}

void SingleList::push_front(int val) {
    insert_(dummy, new ListNode(val));
}

void SingleList::pop_front() {
    assert (cnt>0);
    erase_(dummy);
}

void SingleList::push_back(int val) {
    insert_(loc(cnt), new ListNode(val));
}

void SingleList::pop_back() {
    assert (cnt>0);
    erase_(loc(cnt-1));
}

int & SingleList::front() {
    assert (cnt>0);
    return dummy->next->val;
}

int & SingleList::back() {
    assert (cnt>0);
    return loc(cnt)->val;
}

int & SingleList::at(int idx) {
    assert (idx>=0 && idx < cnt);
    return loc(idx+1)->val;
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void SingleList::reverse() {
    ListNode* prev = nullptr;
    ListNode* cur = dummy->next;
    while (cur) {
        ListNode* tmp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = tmp;
    }
    dummy->next = prev;
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void SingleList::remove(int val) {
    ListNode* cur = dummy;
    while (cur->next) {
        if (cur->next->val==val) {
           erase_(cur); 
        }
        else {
            cur = cur->next;
        }
    }
}

void SingleList::print() const {
    ListNode* cur = dummy->next;
    while (cur) {
        std::cout<<cur->val<<" ";
        cur = cur->next;
    }
    std::cout<<std::endl;
}



int main() {
    SingleList list;
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
    list.clear();
    list.print();
    std::cout<<list.size()<<std::endl;
}
