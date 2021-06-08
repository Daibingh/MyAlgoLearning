#include <stdio.h>
#include "queue.h"

int main() {
    Queue q = CreateQueue(10);

    printf("%d\n", q->size);

    enqueue(1, q);
    enqueue(5, q);
    enqueue(31, q);
    enqueue(11, q);

    while (!isEmpty(q)) {
        printf("%d, %d, %d \n", q->size, back(q), front(q));
        dequeue(q);
    }
    deleteQueue(q);
    return 0;
}