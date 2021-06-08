#include <stdio.h>
#include "hashtable.h"


int main() {
    HashTable h = createHashTable(7);
    insert(33, h);
    insert(43, h);
    insert(10, h);
    insert(9, h);
    insert(23, h);

    printf("%ld\n", find(10, h));
    printf("%ld\n", find(9, h));
    printf("%ld\n", find(1, h));
    deleteKey(10, h);
    printf("%ld\n", find(10, h));

    for (int i=0;i < h->tableSize;++i) {
        printList(h->lists[i]);
    }

    deleteHashTable(h);
}