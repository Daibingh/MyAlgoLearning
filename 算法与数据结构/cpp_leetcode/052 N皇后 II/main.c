#include "bits/stdc++.h"

/*
n 皇后问题 研究的是如何将 n 个皇后放置在 n×n
的棋盘上，并且使皇后彼此之间不能相互攻击。

给你一个整数 n ，返回 n 皇后问题 不同的解决方案的数量
-------------------------------------------------
解法：
- DFS 搜索
- 使用 一维数组，判断是否在一个斜线: 横纵坐标之差的绝对值是否相等
*/

static int g_cnt = 0;

bool IsValid(int row, int col, int* arr, int n) {
    if (arr[col] != -1)
        return false;
    for (int i = 0; i < n; ++i) {
        if (arr[i] == -1) {
            continue;
        }
        // 判断斜线 横纵坐标之差
        if (abs(row - arr[i]) == abs(col - i)) {
            return false;
        }
    }
    return true;
}

void Search(int row, int* arr, int n) {
    if (row == n) {
        ++g_cnt;
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (!IsValid(row, i, arr, n)) {
            continue;
        }
        arr[i] = row;
        Search(row + 1, arr, n);
        arr[i] = -1;
    }
}

int totalNQueens(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    memset(arr, 0xff, n * sizeof(int));
    g_cnt = 0;
    Search(0, arr, n);
    return g_cnt;
}