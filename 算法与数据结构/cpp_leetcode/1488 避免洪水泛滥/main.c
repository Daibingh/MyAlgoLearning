#include "../uthash.h"

/*
 * https://leetcode-cn.com/problems/avoid-flood-in-the-city/
 * 
 */

// 使用 uthash + 线性搜索: 超时
struct Item
{
    int key_;
    UT_hash_handle hh;
};

static struct Item *g_htb = NULL;

void AddHash(int key)
{
    struct Item *ite = (struct Item *)malloc(sizeof(struct Item));
    ite->key_ = key;
    HASH_ADD_INT(g_htb, key_, ite);
}

struct Item * FindHash(int key)
{
    struct Item *ite = NULL;
    HASH_FIND_INT(g_htb, &key, ite);
    return ite;
}

void DeleteHash(struct Item *ite)
{
    HASH_DEL(g_htb, ite);
    free(ite);
}

void DeleteAll()
{
    struct Item *cur = NULL;
    struct Item *tmp = NULL;
    HASH_ITER(hh, g_htb, cur, tmp) {
        HASH_DEL(g_htb, cur);
        free(cur);
    }
}

struct Item * Search(int *rains, int rainsSize, int start)
{
    for (int i=start; i<rainsSize; ++i) {
        struct Item *ite = FindHash(rains[i]);
        if (ite != NULL) {
            return ite;
        }
    }
    return NULL;
}

int* avoidFlood(int* rains, int rainsSize, int* returnSize){
    *returnSize = rainsSize;
    int *res = (int *)malloc(rainsSize * sizeof(int));
    for (int i=0 ; i<rainsSize; ++i) {
        if (rains[i] > 0) {   // rains[i] 下雨
            res[i] = -1;
            if (FindHash(rains[i]) != NULL) {  // rains[i] 以前下过雨，满了
                *returnSize = 0;
                DeleteAll();
                return NULL;
            }
            AddHash(rains[i]);
        } else {  // 晴天
            struct Item *ite = Search(rains, rainsSize, i + 1);  // 搜索以后第一个下雨的湖，且之前下过雨
            if (ite != NULL) {
                res[i] = ite->key_;
                DeleteHash(ite);
            } else {
                res[i] = 1;
            }
        }
    }
    DeleteAll();
    return res;
}