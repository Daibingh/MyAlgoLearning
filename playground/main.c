
// freopen("playground/data.in", "r", stdin);

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../uthash.h"

/*
 * scanf 自动跳过空白字符；先 scanf 再 fgets(按行读函数)
 * 可能会读到空白，尽量统一使用其中一种
 */


#define MAX_SIZE 10000

static int g_numStack[MAX_SIZE];
static char g_opStack[MAX_SIZE];
static size_t g_numCnt = 0;
static size_t g_opCnt = 0;

static unsigned char g_opOrder[128];

void Calc()
{
    char op = g_opStack[--g_opCnt];
    int b = g_numStack[--g_numCnt];
    int a = g_numStack[--g_numCnt];
    if (op == '+') {
        g_numStack[g_numCnt++] = a + b;
    } else if (op == '-') {
        g_numStack[g_numCnt++] = a - b;
    } else if (op == '*') {
        g_numStack[g_numCnt++] = a * b;
    } else if (op == '/') {
        g_numStack[g_numCnt++] = a / b;
    }
}

int calculate(char * s){
    size_t len = strlen(s);
    int i = 0;
    while ( i < len ) {
        if (s[i] == ' ') {
            ++i;
            continue;
        }
        if (isdigit(s[i])) {
            int n = s[i] - '0';
            while (isdigit(s[++i])) {
                n = 10 * n + s[i] - '0';
            }
            g_numStack[g_numCnt++] = n;
        } else {
            while (g_opCnt != 0 && g_opOrder[g_opStack[g_opCnt-1]] >= g_opOrder[s[i]] ) {
                Calc();
            }
            g_opStack[g_opCnt++] = s[i];
            ++i;
        }
    }
    while (g_opCnt > 0) {
        Calc();
    }
    return g_numStack[0];
}

int main(void)
{
    g_opOrder['+'] = 1;
    g_opOrder['-'] = 1;
    g_opOrder['*'] = 2;
    g_opOrder['/'] = 2;
    printf("%d\n", calculate("2*5/2"));
}