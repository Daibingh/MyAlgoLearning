#include <bits/stdc++.h>

using namespace std;

/*
请你为 最不经常使用（LFU）缓存算法设计并实现数据结构。它应该支持以下操作：get 和 put。

get(key) - 如果键存在于缓存中，则获取键的值（总是正数），否则返回 -1。
put(key, value) - 如果键已存在，则变更其值；如果键不存在，请插入键值对。当缓存达到其容量时，则应该在插入新项之前，使最不经常使用的项无效。在此问题中，当存在平局（即两个或更多个键具有相同使用频率）时，应该去除最久未使用的键。
「项的使用次数」就是自插入该项以来对其调用 get 和 put 函数的次数之和。使用次数会在对应项被移除后置为 0 。
*/


/*
解法一：
- 用 红黑树 set 实现自动排序，hash 表 unordered_map 实现查询，两者都持有数据节点，并保持同步
- 查找插入时间复杂度 O(logk)
- 在 C++ 中，set 更新某个元素后，要想重新调整顺序，必须 删除-更新-插入  (更新后重新插入)
*/

struct Node {
    int key;
    int val;
    int feq;
    int tim;

    Node() {}

    Node(int k, int v, int f, int t): key(k), val(v), feq(f), tim(t) {}

    // 自定义排序，前面的最先删除
    bool operator<(const Node& n) const {
        if (feq < n.feq) return true;
        else if (feq == n.feq && tim < n.tim) return true;
        return false;
    }

    bool operator ==(const Node& n) const {
        return key == n.key;
    }
    
};


class LFUCache {
    unordered_map<int, Node> Map;  // Map 和 set 中都持有一份 node，并保持一致
    set<Node> data;
    int cap;
    int cnt;
    
    void visit(Node & n) {
        data.erase(n);
        ++n.feq;
        n.tim = ++cnt;
        data.insert(n);
    }

public:
    LFUCache(int capacity):cap(capacity), cnt(0) {

    }
    
    int get(int key) {
        auto it = Map.find(key);
        if (it==Map.end()) return -1;
        int val = it->second.val;
        visit(it->second);
        return val;
    }
    
    void put(int key, int value) {
        if (cap==0) return ;
        auto it = Map.find(key);
        if (it!=Map.end()) {
            it->second.val = value;
            visit(it->second);
            return;
        }
        if (cap == data.size()) {
            Map.erase(data.begin()->key);
            data.erase(data.begin());
        }
        Node n(key, value, 1, ++cnt);
        data.insert(n);
        Map[key] = n;
    }
};


//////////////////////////////////////////////////////////////////////////////////
//解法二，时间复杂度 O(1)
struct Node {
    int val;
    int feq;
    list<int>::iterator it;
};


class LFUCache {
    int cap;
    int min_f;
    unordered_map<int, Node> key_tab;  // key -> node
    unordered_map<int, list<int>> feq_tab;  // feq -> list of keys 

    // 更新某个node的频率、频率hash表
    void visit(Node& n) {
        int feq_pre = n.feq++;
        feq_tab[n.feq].splice( feq_tab[n.feq].begin(), feq_tab[feq_pre], n.it );
        if (feq_tab[feq_pre].empty() && min_f==feq_pre) // 判断是否更新最小频率
            min_f = n.feq;
        n.it = feq_tab[n.feq].begin();
    }
public:
    LFUCache(int capacity):cap(capacity), min_f(1) {

    }
    
    int get(int key) {
        auto it = key_tab.find(key);
        if (it==key_tab.end()) return -1;
        int val = it->second.val;
        visit(it->second);
        return val;
    }
    
    void put(int key, int value) {
        if (cap==0) return ;
        auto it = key_tab.find(key);
        if (it!=key_tab.end()) {
            it->second.val = value;
            visit(it->second);
            return;
        }
        if (cap == key_tab.size()) {
            int del_key = feq_tab[min_f].back();
            feq_tab[min_f].pop_back();
            key_tab.erase(del_key);
        }
        feq_tab[1].push_front(key);
        key_tab[key] = {value, 1, feq_tab[1].begin()};
        min_f = 1;
    }
};