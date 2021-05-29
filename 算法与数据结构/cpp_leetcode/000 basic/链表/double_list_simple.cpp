#include <bits/stdc++.h>

using namespace std;

struct ListNode {
	ListNode* prev, * next;
	int val;
	ListNode( int v=0 ): val( v ), prev( nullptr ), next( nullptr ) {}
};

// 根据索引插入到指定位置
ListNode* insertListNodeByIndex( ListNode* head, ListNode* newNode, int index ) {
	// 这里假设没有哑节点!!!
	
	if ( ! head ) return newNode;

	if ( index == 0 ) {
		newNode->next = head;
		newNode->next->prev = newNode;
		return newNode;
	}

	ListNode* cur = head;
	while ( --index && cur->next ) {
		cur = cur->next;
	}

	if ( ! cur->next ) {
		cur->next = newNode;
		newNode->prev = cur;
		return head;
	}

	newNode->next = cur->next;
	cur->next = newNode;
	newNode->prev = cur;
	newNode->next->prev = newNode;
	return head;
}


void print_list( ListNode* head ) {
	while ( head ) {
		cout<<head->val<<" ";
		head = head->next;
	}
	cout<<endl;
}

// 根据顺序插入
ListNode* insertListNodeByOrder( ListNode* head, ListNode* newNode ) {
	if ( ! head ) return newNode;
	if ( newNode->val < head->val ) {
		newNode->next = head;
		head->prev = newNode;
		return newNode;
	}

	ListNode* cur = head;
	while ( cur->next && cur->next->val < newNode->val ) {
		cur = cur->next;
	}
	if ( ! cur->next ) {
		cur->next = newNode;
		newNode->prev = cur;
		return head;
	}
	newNode->next = cur->next;
	cur->next = newNode;
	newNode->prev = cur;
	newNode->next->prev = newNode;
	return head;

}

int main() {
	
	ListNode* l1 = new ListNode( 0 );
	ListNode* l2 = new ListNode( 2 );
	ListNode* l3 = new ListNode( 4 );
	ListNode* l4 = new ListNode( 6 );

	l1->next = l2;
	l2->next = l3;
	l3->next = l4;

	l4->prev = l3;
	l3->prev = l2;
	l2->prev = l1;

	ListNode* head = l1;
	print_list( head );

	ListNode* newNode = new ListNode( 10 );

	// head = insertListNodeByIndex( head, newNode, 10 );
	head = insertListNodeByOrder( head, newNode );

	print_list( head );

	return 0;
}

