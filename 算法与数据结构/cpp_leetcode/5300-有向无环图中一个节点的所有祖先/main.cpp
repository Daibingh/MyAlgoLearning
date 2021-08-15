
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

/*
给你一个正整数 n ，它表示一个 有向无环图 中节点的数目，节点编号为 0 到 n - 1 （包括两者）。

给你一个二维整数数组 edges ，其中 edges[i] = [fromi, toi] 表示图中一条从 fromi 到 toi 的单向边。

请你返回一个数组 answer，其中 answer[i]是第 i 个节点的所有 祖先 ，这些祖先节点 升序 排序。

如果 u 通过一系列边，能够到达 v ，那么我们称节点 u 是节点 v 的 祖先 节点。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/all-ancestors-of-a-node-in-a-directed-acyclic-graph
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

/* 反向建图遍历 */

#define N 1005

int g_graphRev[N][N];
int g_nCols[N];
int g_res[N][N];
int g_resSize[N];

void BuildGraph(int** edges, int edgesSize, int* edgesColSize) {
    for (int i=0; i< edgesSize; ++i) {
        g_graphRev[edges[i][1]][g_nCols[edges[i][1]]++] = edges[i][0];
    }
}

void Travel(int root, int cur, int *visited) {
    for (int i=0; i<g_nCols[cur]; ++i) {
        int next = g_graphRev[cur][i];
        if (visited[next] == 1) {
            continue;
        }
        visited[next] = 1;
        g_res[root][g_resSize[root]++] = next;
        Travel(root, next, visited);
    }
}

int Comp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int** getAncestors(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize, int** returnColumnSizes){
    memset(g_graphRev, 0, sizeof(g_graphRev));
    memset(g_nCols, 0, sizeof(g_nCols));
    memset(g_resSize, 0, sizeof(g_resSize));
    BuildGraph(edges, edgesSize, edgesColSize);

    for (int i=0; i<n; ++i) {
        int visited[N] = {0};
        Travel(i, i, visited);
        qsort(g_res[i], g_resSize[i], sizeof(g_res[i][0]), Comp);
    }
    *returnSize = n;
    *returnColumnSizes = (int *)malloc(n * sizeof(int));
    int **res = (int **)malloc(n * sizeof(int*));
    for (int i=0;i<n;++i) {
        (*returnColumnSizes)[i] = g_resSize[i];
        res[i] = (int *)malloc(g_resSize[i] * sizeof(int));
        memcpy(res[i], g_res[i], g_resSize[i] * sizeof(int));
    }
    return res;
}