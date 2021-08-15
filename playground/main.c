
// freopen("playground/data.in", "r", stdin);

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../uthash.h"


#define N 5000
#define L 13
static char g_res[N][L];
static int g_cnt = 0;
static int g_len = 0;

void solve(char *s, int pos) {
    for (int i=pos;i<g_len;++i) {
        if (isdigit(s[i])) {
            continue;
        }
        strcpy(g_res[g_cnt++], s);
        char c = s[i];
        if (isupper(s[i])) {
            s[i] = tolower(s[i]);
        } else {
            s[i] = toupper(s[i]);
        }
        strcpy(g_res[g_cnt++], s);
        solve(s, pos+1);
        s[i] = c;
    }
}

char ** letterCasePermutation(char * s, int* returnSize) {
    g_len = strlen(s);
    g_cnt = 0;
    solve(s, 0);
    *returnSize = g_cnt;
    return g_res;
}