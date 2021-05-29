#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define MAP_SIZE 128

int match(char* pattern, char* word) {
    int len1 = strlen(pattern);
    int len2 = strlen(word);
    if (len1 != len2)
        return 0;
    unsigned char map[MAP_SIZE], map2[MAP_SIZE];
    memset(map, 0, MAP_SIZE * sizeof(unsigned char));
    memset(map2, 0, MAP_SIZE * sizeof(unsigned char));
    for (int i = 0; i < len1; ++i) {
        if (map[pattern[i]] == 0)
            map[pattern[i]] = word[i];
        else if (map[pattern[i]] != word[i])
            return 0;

        if (map2[word[i]] == 0)
            map2[word[i]] = pattern[i];
        else if (map2[word[i]] != pattern[i])
            return 0;
    }
    return 1;
}

char** findAndReplacePattern(char** words,
                             int wordsSize,
                             char* pattern,
                             int* returnSize) {
    char** res = (char**)malloc(wordsSize * sizeof(char*));
    *returnSize = 0;
    for (int i = 0; i < wordsSize; ++i) {
        if (match(pattern, words[i])) {
            res[(*returnSize)++] = words[i];
        }
    }
    return res;
}