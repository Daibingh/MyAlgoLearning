
// freopen("playground/data.in", "r", stdin);

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUF_SIZE 1024
#define ARRAY_SIZE 147456
#define MAX_LINE 16384


struct HashItem {
    int key;
    int val;
};


struct ListNode {
    int node;
    struct ListNode *next;
};


int inputArray[ARRAY_SIZE];
int arraySize = 0;
int offset[MAX_LINE];
int offsetSize = 0;
struct HashItem nodeIdMap[MAX_LINE];


void printArray(int *arr, int len) {
    for (int i=0; i<len; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("size: %d\n", len);
}


void addHash(int key, int val) {
    int pos = key % MAX_LINE;
    while (nodeIdMap[pos].key != -1 && nodeIdMap[pos].key != key) {
        pos = ( pos + 1) % MAX_LINE;
    }
    if (nodeIdMap[pos].key == -1) {
        nodeIdMap[pos].key = key;
        nodeIdMap[pos].val = val; 
    }
}


int getHash(int key) {
    int pos = key % MAX_LINE;
    while (nodeIdMap[pos].key != -1 && nodeIdMap[pos].key != key) {
        pos = ( pos + 1) % MAX_LINE;
    }
    return nodeIdMap[pos].val;
}

void removeHash(int key) {
    int pos = key % MAX_LINE;
    while (nodeIdMap[pos].key != -1 && nodeIdMap[pos].key != key) {
        pos = ( pos + 1) % MAX_LINE;
    }
    nodeIdMap[pos].val = -100;
}


void buildHashMap() {
    for (int i=0;i<offsetSize;++i) {
        addHash(inputArray[offset[i]], i);
    }
}

int parseInput() {
    char buf[BUF_SIZE];
    while (fgets(buf, BUF_SIZE, stdin)) {
        // printf("%s", buf);
        char *num = NULL;
        offset[++offsetSize] = offset[offsetSize];
        for (num = strtok(buf, " "); num != NULL; num = strtok(NULL, " ")) {
            if (isdigit(*num)) {
                inputArray[arraySize++] = atoi(num); 
                offset[offsetSize]++;
            }
        }
    }
}

void dfs(int startId) {
    int val = getHash(startId);
    if (val == -100) return;
    printf("%d\n", startId);
    removeHash(startId);
    if (val==-1) return;
    for (int i=offset[val]+1; i<offset[val+1]; ++i) {
        dfs(inputArray[i]);
    }
}


int main(int argc, char **argv) {
    
    if (argc < 3) {
        puts("usage: <this_exe> <input_file> <output_file>");
        return -1;
    }

    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);

    memset(nodeIdMap, -1, MAX_LINE * sizeof(struct HashItem));

    parseInput();

    // printArray(offset, offsetSize+1);
    // printArray(inputArray, arraySize);

    buildHashMap();

    // for (int i=0;i<10;++i) {
    //     printf("%d, %d\n", nodeIdMap[i].key, nodeIdMap[i].val);
    // }

    dfs(0);

    return 0;
}
