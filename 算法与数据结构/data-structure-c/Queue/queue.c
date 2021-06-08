#include "queue.h"
#include <assert.h>
#include <stdlib.h>

Queue CreateQueue(int maxSize) {
    Queue q = (Queue)malloc(sizeof(struct _Queue));
    q->array = (int*)malloc(sizeof(int) * maxSize);
    q->capacity = maxSize;
    makeEmpty(q);
}

int isEmpty(Queue q) {
    return q->size == 0;
}

int isFull(Queue q) {
    return q->size == q->capacity;
}

void makeEmpty(Queue q) {
    q->size = 0;
    q->front = 1;
    q->rear = 0;
}

void enqueue(int x, Queue q) {
    assert(!isFull(q));
    ++q->size;
    if (++q->rear == q->capacity)
        q->rear = 0;
    q->array[q->rear] = x;
}

void dequeue(Queue q) {
    assert(!isEmpty(q));
    --q->size;
    if (++q->front == q->capacity)
        q->front = 0;
}

int back(Queue q) {
    assert(!isEmpty(q));
    return q->array[q->rear];
}

int front(Queue q) {
    assert(!isEmpty(q));
    return q->array[q->front];
}

void deleteQueue(Queue q) {
    assert(q != NULL);
    free(q->array);
    free(q);
}
