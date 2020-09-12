#include "utils.hpp"

using namespace std;

/*
运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制。它应该支持以下操作： 获取数据 get 和 写入数据 put 。

获取数据 get(key) - 如果关键字 (key) 存在于缓存中，则获取关键字的值（总是正数），否则返回 -1。
写入数据 put(key, value) - 如果关键字已经存在，则变更其数据值；如果关键字不存在，则插入该组「关键字/值」。当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。
---------------------------------------------------------------

用到的数据结构
- 双向链表 插入和删除都是 O(1) 存数据对
- hash 表 查找是 O(1) 链表节点地址

*/

class LRUCache {
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        auto it = m.find(key);
        if (it==m.end()) return -1;
        cache.splice(cache.begin(), cache, it->second); // splice std::list 移花接木 splice(pos, list, it) 将 list 的 it 节点 接入 当前list 的 pos 位置， it 没有失效，跟着节点走
        return it->second->second;
    }
    
    void put(int key, int value) {
        auto it = m.find(key);
        if (it!=m.end()) {   // 如果原来就存在 key 就更新一下 value，将该节点移到最前面
            it->second->second = value;
            cache.splice(cache.begin(), cache, it->second);
            return;  // 这里要 return
        }
        // 否则就是要新插入一个节点，先看看原来是否是满的， 如果是满的先移除最后一个节点
        if (cache.size() == capacity) {
             auto & last = cache.back();
             m.erase(last.first);  // list 存key的目的就是删除时方便
             cache.pop_back();
        }
        // 在最前面插入节点
        cache.emplace_front(key, value);
        m[key] = cache.begin();  // key 插入 hash 表
    }

private:
    list<pair<int,int>> cache;
    unordered_map<int, list<pair<int,int>>::iterator > m;
    int capacity;
};
