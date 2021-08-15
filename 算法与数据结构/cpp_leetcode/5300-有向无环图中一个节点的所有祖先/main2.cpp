
/* 正向建图 */

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define N 1005

int g_graph[N][N];
int g_nCols[N];
int g_res[N][N];
int g_resSize[N];

void BuildGraph(int** edges, int edgesSize, int* edgesColSize) {
    for (int i=0; i< edgesSize; ++i) {
        g_graph[edges[i][0]][g_nCols[edges[i][0]]++] = edges[i][1];
    }
}

void Travel(int root, int cur, int *visited) {
    for (int i=0; i<g_nCols[cur]; ++i) {
        int next = g_graph[cur][i];
        if (visited[next] == 1) {
            continue;
        }
        visited[next] = 1;
        g_res[next][g_resSize[next]++] = root;
        Travel(root, next, visited);
    }
}

int Comp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int** getAncestors(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize, int** returnColumnSizes){
    memset(g_graph, 0, sizeof(g_graph));
    memset(g_nCols, 0, sizeof(g_nCols));
    memset(g_resSize, 0, sizeof(g_resSize));
    BuildGraph(edges, edgesSize, edgesColSize);

    for (int i=0; i<n; ++i) {
        int visited[N] = {0};
        Travel(i, i, visited);
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