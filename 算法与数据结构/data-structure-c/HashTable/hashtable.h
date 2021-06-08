#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

/*
hash 表实现，链地址法解决冲突
- key 为 int
- hash 函数取模运算
- 链表带表头
*/

#include "list.h"

struct HashTbl;
typedef struct HashTbl* HashTable;

HashTable createHashTable(int tableSize);
void deleteHashTable(HashTable h);
Position find(int key, HashTable h);
void insert(int key, HashTable h);
void makeEmpty(HashTable h);
void deleteKey(int key, HashTable h);

struct HashTbl {
    int tableSize;
    List* lists;
};

#endif