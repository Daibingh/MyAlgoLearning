#include <stdio.h>
#include <string.h>

int lengthOfLastWord(char* s) {
    int cnt = 0;
    char* p = s + strlen(s) - 1;
    for (; p >= s && *p == ' '; --p)
        ;
    for (; p >= s && *p != ' '; --p, ++cnt)
        ;
    return cnt;
}

int main() {
    char* s = "abc--- hello ";
    int res = lengthOfLastWord(s);
    printf("%d\n", res);
}