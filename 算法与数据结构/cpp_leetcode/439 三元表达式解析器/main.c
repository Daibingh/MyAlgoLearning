

#define MAX_SIZE 20000


char parseTernary( char *s) {
    char stk[MAX_SIZE];
    int size = 0;
    int len = strlen(s);
    for (int i = len - 1; i >= 0; --i) {
        char c = s[i];
        if (size && stk[size-1] == '?') {
            --size;
            char first = stk[size-1];   
            --size;
            --size;
            char second = stk[size-1]; 
            --size;
            stk[size++] = c == 'T' ? first : second;
        } else {
            stk[size++] = c;
        }
    }
    return stk[size-1];
}