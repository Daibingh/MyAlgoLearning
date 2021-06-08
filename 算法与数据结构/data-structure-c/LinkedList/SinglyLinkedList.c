#include "SinglyLinkedList.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    Pos next;
};

int isEmpty(List l) {
    assert(l != NULL);
    return l->next == NULL;
}

List createList() {
    List l = (List)malloc(sizeof(struct Node));
    l->next = NULL;
    return l;
}

int isLast(Pos p) {
    assert(p != NULL);
    return p->next == NULL;
}

Pos find(int x, List l) {
    // assert(l != NULL);
    // Pos p = l->next;
    // while (p != NULL && p->val != x) {
    //     p = p->next;
    // }
    // return p;
    return findPrevious(x, l)->next;
}

Pos findPrevious(int x, List l) {
    assert(l != NULL);
    Pos p = l;
    while (!isLast(p) && p->next->val != x) {
        p = p->next;
    }
    return p;
}

void makeEmpty(List l) {
    assert(l != NULL);
    Pos p = l->next;
    while (p != NULL) {
        Pos tmp = p->next;
        free(p);
        p = tmp;
    }
}

void deleteList(List l) {
    assert(l != NULL);
    makeEmpty(l);
    free(l);
}

void deleteByValue(int x, List l) {
    assert(l != NULL);
    Pos p = l;
    while (!isLast(p)) {
        if (p->next->val == x) {
            deleteByPos(p);
        } else {
            p = p->next;
        }
    }
}

void deleteByPos(Pos prev) {
    assert(!isLast(prev));
    Pos tmp = prev->next;
    prev->next = tmp->next;
    free(tmp);
}

void insertByPos(int x, Pos prev) {
    assert(prev != NULL);
    Pos newNode = (Pos)malloc(sizeof(struct Node));
    newNode->next = NULL;
    newNode->val = x;
    newNode->next = prev->next;
    prev->next = newNode;
}

void insertByIndex(int x, List l, int index) {
    assert(l != NULL);
    Pos p = l;
    while (--index && !isLast(p)) {
        p = p->next;
    }
    insertByPos(x, p);
}

void printList(List l) {
    assert(l != NULL);
    Pos p = l->next;
    while (p != NULL) {
        printf("%d -> ", p->val);
        p = p->next;
    }
    printf("NULL\n");
}