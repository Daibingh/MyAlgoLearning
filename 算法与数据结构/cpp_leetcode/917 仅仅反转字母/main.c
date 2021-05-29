#include <string.h>
#include <stdio.h>

inline int isAlpha(char c) {
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' ;
}

inline void swap( char * s, char * p ) {
    char t = *s;
    *s = *p;
    *p = t;
}

char * reverseOnlyLetters(char * s){
    char * l = s;
    char * r = s + strlen(s);
    while ( l < r ) {
        while ( !isAlpha( *l ) && l < r  ) ++l;
        while ( !isAlpha( *r ) && l < r  ) --r;
        swap(l++, r--);

    }
    return s;
}

int main() {
    char * s = "abd0dfew!---3dl";
    s = reverseOnlyLetters(s);
    printf("%s\n", s);
}