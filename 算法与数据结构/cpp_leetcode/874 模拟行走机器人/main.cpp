#include "../uthash.h"
#include <math.h>

/*
- https://leetcode-cn.com/problems/walking-robot-simulation/
----------------------------------
难点：
- 方向的处理 dx, dy 数组
- 使用 uthash 查找障碍物

*/

typedef struct {
    int x;
    int y;
} ItemKey;

typedef struct {
    ItemKey key_;
    UT_hash_handle hh;
} Item;

static Item *g_items = NULL;

Item *HashFind(int x, int y)
{
    ItemKey itKey;
    itKey.x = x;
    itKey.y = y;
    Item *it = NULL;
    HASH_FIND(hh, g_items, &itKey, sizeof(ItemKey), it);
    return it;
}

void HashAdd(int x, int y)
{
    Item *it = (Item *)malloc(sizeof(Item));
    it->key_.x = x;
    it->key_.y = y;
    HASH_ADD(hh, g_items, key_, sizeof(ItemKey), it);
}

void DeleteAll()
{
    Item *cur = NULL;
    Item *tmp = NULL;
    HASH_ITER(hh, g_items, cur, tmp) {
        HASH_DEL(g_items, cur);
        free(cur);
    }
}

int robotSim(int* commands, int commandsSize, int** obstacles, int obstaclesSize, int* obstaclesColSize){
    g_items = NULL;
    for (int i=0; i<obstaclesSize; ++i) {
        Item *it = HashFind(obstacles[i][0], obstacles[i][1]);
        if (it == NULL) {
            HashAdd(obstacles[i][0], obstacles[i][1]);
        }
    }
    int x = 0;
    int y = 0;
    int res = 0;
    int direct = 0;
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    for (int i=0;i<commandsSize;++i) {
        int cmd = commands[i];
        if (cmd == -1) {
            direct = (direct + 1) % 4;
        } else if (cmd == -2) {
            direct = (direct + 3) % 4;
        } else {
            for (int k = 0; k < cmd; ++k) {
                int x1 = x + dx[direct];
                int y1 = y + dy[direct];
                if (HashFind(x1, y1) != NULL) {
                    break;
                }
                x = x1;
                y = y1;
                res = fmax(res, x * x + y * y);
            }
        }
    }
    DeleteAll();
    return res;
}