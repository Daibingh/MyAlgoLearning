#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int isEmpty(List l) {
    assert(l != NULL);
    return l->next == NULL;
}

List createList() {
    List l = (List)malloc(sizeof(struct ListNode));
    l->next = NULL;
    return l;
}

int isLast(Position p) {
    assert(p != NULL);
    return p->next == NULL;
}

Position _find(int x, List l) {
    return findPrevious(x, l)->next;
}

Position findPrevious(int x, List l) {
    assert(l != NULL);
    Position p = l;
    while (!isLast(p) && p->next->val != x) {
        p = p->next;
    }
    return p;
}

void _makeEmpty(List l) {
    assert(l != NULL);
    Position p = l->next;
    while (p != NULL) {
        Position tmp = p->next;
        free(p);
        p = tmp;
    }
}

void deleteList(List l) {
    assert(l != NULL);
    _makeEmpty(l);
    free(l);
}

void deleteByValue(int x, List l) {
    assert(l != NULL);
    Position p = l;
    while (!isLast(p)) {
        if (p->next->val == x) {
            deleteByPosition(p);
        } else {
            p = p->next;
        }
    }
}

void deleteByPosition(Position prev) {
    assert(!isLast(prev));
    Position tmp = prev->next;
    prev->next = tmp->next;
    free(tmp);
}

void insertByPosition(int x, Position prev) {
    assert(prev != NULL);
    Position newListNode = (Position)malloc(sizeof(struct ListNode));
    newListNode->next = NULL;
    newListNode->val = x;
    newListNode->next = prev->next;
    prev->next = newListNode;
}

void insertByIndex(int x, List l, int index) {
    assert(l != NULL);
    Position p = l;
    while (--index && !isLast(p)) {
        p = p->next;
    }
    insertByPosition(x, p);
}

void printList(List l) {
    assert(l != NULL);
    Position p = l->next;
    while (p != NULL) {
        printf("%d -> ", p->val);
        p = p->next;
    }
    printf("NULL\n");
}