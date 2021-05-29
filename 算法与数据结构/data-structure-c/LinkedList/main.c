#include "SinglyLinkedList.h"


int main() {

	List l = createList();
	insertByIndex(1,l,1);
	insertByIndex(2,l,2);
	insertByIndex(3,l,3);
	insertByIndex(3,l,3);
	insertByIndex(3,l,3);
	insertByIndex(3,l,3);
	insertByIndex(2,l,4);

	printList(l);
	deleteByValue(3, l);
	printList(l);
    return 0;
}