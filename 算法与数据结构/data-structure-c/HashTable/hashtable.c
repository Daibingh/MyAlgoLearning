#include "hashtable.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>


static int nextPrimeNumber(int n) {
    while (1) {
        int found = 1;
        int q = sqrt(n);
        for (int i = 2; i <= q; ++i) {
            if (n % i == 0) {
                found = 0;
                break;
            }
        }
        if (found)
            return n;
        ++n;
    }
}

static int hash(int key, HashTable h) {
    return key % h->tableSize;
}

HashTable createHashTable(int tableSize) {
    HashTable h = (HashTable)malloc(sizeof(struct HashTbl));
    tableSize = nextPrimeNumber(tableSize);
    h->tableSize = tableSize;
    h->lists = (List*)malloc(tableSize * sizeof(List));
    for (int i = 0; i < tableSize; ++i) {
        h->lists[i] = (List)malloc(sizeof(struct ListNode));
        h->lists[i]->next = NULL;
    }
    return h;
}

void deleteHashTable(HashTable h) {
    assert(h != NULL);
    for (int i = 0; i < h->tableSize; ++i) {
        deleteList(h->lists[i]);
    }
    free(h);
}

Position find(int key, HashTable h) {
    int idx = hash(key, h);
    return _find(key, h->lists[idx]);
}

void insert(int key, HashTable h) {
    int idx = hash(key, h);
    if (_find(key, h->lists[idx]) == NULL) {
        Position node = (Position)malloc(sizeof(struct ListNode));
        node->val = key;
        node->next = h->lists[idx]->next;
        h->lists[idx]->next = node;
    }
}

void makeEmpty(HashTable h) {
    assert(h != NULL);
    for (int i = 0; i < h->tableSize; ++i) {
        _makeEmpty(h->lists[i]);
    }
}

void deleteKey(int key, HashTable h) {
    int idx = hash(key, h);
    Position p = findPrevious(key, h->lists[idx]);
    if (!isLast(p)) {
        Position tmp = p->next;
        p->next = p->next->next;
        free(tmp);
    }
}