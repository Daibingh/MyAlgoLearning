#include "stdlib.h"

/*
C 语言实现
- 数组模拟 hash
- 双向链表（带头尾哑节点）
*/

#define N 10005

typedef struct Item {
    int key;
    int val;
    struct Item *prev;
    struct Item *next;
} Item;

static Item *g_map[N];

static Item *head = NULL;
static Item *tail = NULL;
static int g_cnt = 0;
static int g_cap = 0;


typedef struct {

} LRUCache;


LRUCache* lRUCacheCreate(int capacity) {
    memset(g_map, 0, N * sizeof(Item *));
    g_cnt = 0;
    g_cap = capacity;
    head = (Item *)malloc(sizeof(Item));
    memset(head, 0, sizeof(Item));
    tail = (Item *)malloc(sizeof(Item));
    memset(tail, 0, sizeof(Item));
    head->next = tail;
    tail->prev = head;
    return NULL;
}

void MoveToHead(Item *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = head->next;
    head->next = node;
    node->prev = head;
    node->next->prev = node;
}

void InsertOnHead(Item *new)
{
    new->next = head->next;
    head->next = new;
    new->prev = head;
    new->next->prev = new;
}

int lRUCacheGet(LRUCache* obj, int key) {
    if (g_map[key] == NULL) return -1;
    MoveToHead(g_map[key]);
    return g_map[key]->val;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    if (g_map[key] != NULL) {
        g_map[key]->val = value;
        MoveToHead(g_map[key]);
        return;
    }
    if (g_cnt == g_cap) {
        g_map[tail->prev->key] = NULL;
        tail->prev = tail->prev->prev;
        tail->prev->next = tail;
    }
    Item * new = (Item *)malloc(sizeof(Item));
    memset(new, 0, sizeof(Item));
    new->val = value;
    new->key = key;
    g_map[key] = new;
    InsertOnHead(new);
    g_cnt = fmin(++g_cnt, g_cap);
}

void lRUCacheFree(LRUCache* obj) {

}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/