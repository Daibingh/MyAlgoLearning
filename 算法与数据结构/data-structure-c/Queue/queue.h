#ifndef __QUEUE_H__
#define __QUEUE_H__

struct _Queue;
typedef struct _Queue* Queue;

int isEmpty(Queue q);
int isFull(Queue q);
Queue CreateQueue(int maxSize);
void makeEmpty(Queue q);
void enqueue(int x, Queue q);
void dequeue(Queue q);
int back(Queue q);
int front(Queue q);
void deleteQueue(Queue q);

struct _Queue {
    int capacity;
    int front;
    int rear;
    int size;
    int* array;
};

#endif