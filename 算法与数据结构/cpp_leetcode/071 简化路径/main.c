#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

// solution 1
char* simplifyPath(char* path) {
    char* res = (char*)malloc(MAX_SIZE * sizeof(char));
    int stk[MAX_SIZE];
    memset(res, 0, MAX_SIZE * sizeof(char));
    memset(stk, 0, MAX_SIZE * sizeof(int));
    int cur = 0;
    int t = 0;
    int length = strlen(path);
    int i = 0, j = 1;
    while (i < length) {
        while (path[j] != '/' && j < length)
            ++j;
        if (j - i == 1 || (j - i == 2 && path[i + 1] == '.')) {
            // case 1: "/", "/." , do nothing
        } else if (j - i == 3 && path[i + 1] == '.' && path[i + 2] == '.') {
            // case 2: "/.." , stack pop back
            if (t > 0) {
                cur = stk[--t];
            }
        } else {
            // other cases. copy substring
            stk[t++] = cur;
            memcpy(res + cur, path + i, (j - i) * sizeof(char));
            cur += j - i;
        }
        i = j++;
    }
    if (cur == 0) {
        res[cur++] = '/';
    }
    res[cur] = '\0';
    return res;
}

// solution 2
char* simplifyPath2(char* path) {
    char* stk[MAX_SIZE];
    int size = 0;
    for (char* s = strtok(path, "/"); s; s = strtok(NULL, "/")) {
        if (strcmp(s, ".") == 0) {
            // do nothing
        } else if (strcmp(s, "..") == 0) {
            size = fmax(0, size - 1);
        } else {
            stk[size++] = s;
        }
    }
    if (size == 0)
        return "/";
    char* res = (char*)malloc(MAX_SIZE * sizeof(char));
    *res = '\0';
    for (int i = 0; i < size; ++i) {
        strcat(res, "/");
        strcat(res, stk[i]);
    }
    return res;
}

int main() {
    char* s = "/a/../../b/..";
    s = simplifyPath2(s);
    printf("%s\n", s);
}