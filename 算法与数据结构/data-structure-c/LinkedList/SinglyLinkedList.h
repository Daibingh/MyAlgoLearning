#ifndef _SINGLE_LIST_H
#define _SINGLE_LIST_H

/*

单向链表的 C 语言实现
带哑节点

[dummy]->[1]->[2]->[3]->NULL

*/

struct Node;
typedef struct Node* List;  // 表示表头
typedef struct Node* Pos;   // 表示元素

void deleteList(List l);  // 删除表，包括哑节点
List createList();        // 创建一个空表
int isEmpty(List l);     // 判断是否是空表： 只有哑节点的是空表
void makeEmpty(List l);  // 清空链表
int isLast(Pos p);  // 判断该元素是否是最后一个，最后一个的下一个必然是NULL，反之亦然
Pos find(int x, List l);  // 根据值查找指定元素的位置,第一个
void deleteByValue(int x, List l);  // 删除所有等于x的元素
void deleteByPos(Pos prev);         // 删除prev之后的一个元素
Pos findPrevious(int x, List l);    // 找值为x的前一个元素
void insertByPos(int x, Pos p);     // 根据位置插入
void insertByIndex(int x, List l, int index);  // 根据索引插入, 哑节点index=0
void sort(List l);                             // 排序
void printList(List l);
#endif