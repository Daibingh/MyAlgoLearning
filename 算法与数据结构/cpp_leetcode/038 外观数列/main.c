#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define N 10000


void helper(char * s1, char * s2, int* len) {

    int i = 0, j = 0;
    int k = 0;
    while ( i<*len ) {
        while (s1[i]==s1[j] && j<*len) {
        	++j;
        }
        s2[k++] = j-i+'0';
        s2[k++] = s1[i];
        i = j;
    }
    *len = k;
}


inline void swap(char** s, char ** p) {
    char * t = *s;
    *s = *p;
    *p = t;
}


char * countAndSay(int n){

    char * s1 = (char*)malloc(N*sizeof(char));
    char * s2 = (char*)malloc(N*sizeof(char));
    memset(s1, 0, N);
    memset(s2, 0, N);
    s1[0] = '1';
    int i = 1;
    int len = 1;
    for (; i<n; ++i) {
        helper(s1, s2, &len);
        swap(&s1, &s2);
        // printf("%s\n", s1);
    }
    free(s2);
    return s1;
}

int main() {

	char * s = countAndSay(4);
	printf("%s\n", s);
}