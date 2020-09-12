#include <bits/stdc++.h>
#include "utils.hpp"

////////////////////////////////////////实现 Vector////////////////////////////////////////

template <typename T>
class Vector
{
    private:
    size_t theSize;
    size_t theCapacity;
    T* data;

public:
    explicit Vector(size_t initSize=0): theSize(initSize), theCapacity(initSize) {
        data = new T[theCapacity];
    }

    Vector(size_t initSize, T val): theSize(initSize), theCapacity(initSize) {
        data = new T[theCapacity];
        for (int i=0;i<initSize;++i) {
            data[i] = val;
        }
    }
    
    const Vector & operator= (const Vector& vec) {
        if (this != &vec) {  // 自己不能给自己赋值
            theSize = vec.theSize;
            theCapacity = vec.theCapacity;
            delete [] data;
            data = new T[theCapacity];
            for (int i=0;i<theSize;++i) {
                data[i] = vec[i];
            }
        }
        return *this;
    }

    Vector(const Vector& vec) {
        operator=(vec);  // 调用赋值构造函数
    }

    ~Vector() {
        delete [] data;
    }

    size_t size() const { return theSize; } 

    size_t capacity() const {return theCapacity; }

    void reserve(size_t newCapacity) {
        if (newCapacity < theSize) return;  // 改变容量，当 newCapacity 比 size 小时，什么都不做，否则有内存拷贝
        T* oldData = data;
        data = new T[newCapacity];
        for (int i=0;i<theSize;++i) {
            data[i] = oldData[i];
        }
        delete [] oldData;
        theCapacity = newCapacity;
    }

    void resize(size_t newSize) {
        if (newSize > theCapacity) {
            reserve(2*newSize+1);
        }
        theSize = newSize;
    }

    T& operator[] (size_t index) {
        return data[index];
    }

     const T& operator[] (size_t index) const {
        return data[index];
    }

    bool empty() const {
        return theSize==0;
    }

    void push_back(const T& val) {
        if (theSize==theCapacity) {
            reserve(2 * theSize + 1);
        }
        data[theSize++] = val;
    }

    void pop_back() {
        --theSize;
    }

    void clear() { theSize = 0; }

    const T& back() const {
        return data[theSize-1];
    }

    typedef T* iterator;
    typedef const T* const_iterator;

    iterator begin() { return data; }

    const_iterator begin() const { return data; }

    iterator end() { return data + theSize; }

    const_iterator end() const { return data + theSize; }

};

//////////////////////////////////////实现单向链表////////////////////////////////////


template <typename T>
class List
{

private:

    struct Node
    {
        T data;
        Node* next;
        Node(): next(nullptr) {}
        Node(const T& t): data(t), next(nullptr) {}
    };

public:
    class Iterator
    {
        Node* it;
    public:
        Iterator(Node* i):it(i) {}
        Iterator& operator++() {it=it->next; return *this;}
        Iterator& operator++(int) {Iterator old = it; it=it->next; return old;}
        T& operator *() {return it->data;}
        bool operator!=(const Iterator i) const {return it!=i.it;}
    };

    Iterator begin() {
        return Iterator(head->next);
    }

    Iterator end() {
        return Iterator(tail->next);
    }

    List():cnt(0) {
        head = new Node();
        tail = head;
    }
    ~List() {
        Node* cur = head;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    size_t size() const {
        return cnt;
    }

    bool empty() const {
        return head->next==nullptr;
    }

    void push(const T& t) {
        tail->next = new Node(t);
        tail = tail->next;
        ++cnt;
    }

    void pop() {
        assert (cnt > 0);
        Node* tmp = head->next->next;
        delete head->next;
        head->next = tmp;
        --cnt;
        if (!cnt) tail = head;
    }

    T& top() const {
        assert (cnt >0 );
        return head->next->data;
    }

private:
    
    Node* head;
    Node* tail;
    size_t cnt;

};


/////////////////////////////////////实现双向链表/////////////////////////////////////

template <class T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();
	int append(T data);
    T take();
    void printList() const;
	int size() const;
    bool isEmpty() const;
private:
	class Node
	{
	public:
		Node() {}
		Node(T data)
		{
			this->data = data;
		}
		~Node() {}

		Node* pre;
		Node* next;	
		T data;	
	};

	Node* head;
	Node* tail;
	int count;
};

template <class T>
LinkedList<T>::LinkedList()
{
	count = 0;
	head = tail = NULL;
}

template <class T>
bool LinkedList<T>::isEmpty() const
{
    return head == NULL;
}

template <class T>
LinkedList<T>::~LinkedList()
{
	Node* p = head;
	while(p!=NULL)
	{
		Node* p_next = p->next;
		delete p;
		p = p_next;
	}
}

template <class T>
int LinkedList<T>::append(T data)
{
    if(isEmpty())
	{
		head = tail = new Node(data);
		head->pre = head->next = NULL;
	}
	else
	{
		Node* temp = new Node(data);
		tail->next = temp;
		temp->pre = tail;
		temp->next = NULL;
		tail = temp;
	}
	return ++count;
}

template <class T>
T LinkedList<T>::take()
{
    assert(!isEmpty());
    T data = head->data;
    head = head->next;
    return data;
}

template <class T>
void LinkedList<T>::printList() const
{
    if(isEmpty())  // 常成员函数只能调用常成员函数
	{
		std::cout<<"null"<<std::endl;
		return;
	}
	Node* p = head;
	while(p!=NULL)
	{
		std::cout<<p->data<<std::endl;
		p = p->next;
	}
}

template <class T>
int LinkedList<T>::size() const
{
	return count;
}

// 多项式结构
struct Item
{
    int cof;
    int exr;
    Item() {}
    Item(int c, int e):cof(c),exr(e) {}
};

int main() {


    // Vector<int> v;
    // for (int i=0;i<100;++i) {
    //     v.push_back(i);
    //     std::cout<<"size: "<<v.size()<<", capacity: "<<v.capacity()<<std::endl;
    // }

    // 多项式加法
    List<Item> L1, L2;

    L1.push(Item(6, 5));
    L1.push(Item(1, 2));
    L1.push(Item(2, 0));

    L2.push(Item(6, 3));
    L2.push(Item(5, 2));
    L2.push(Item(2, 1));

    List<Item> L;
    while (!L1.empty() && !L2.empty())
    {
        if (L1.top().exr > L2.top().exr) {
            L.push(L1.top());
            L1.pop();
        }
        else if (L1.top().exr < L2.top().exr) {
            L.push(L2.top());
            L2.pop();
        } else {
            L.push(Item(L1.top().cof+L2.top().cof, L1.top().exr));
            L1.pop();
            L2.pop();
        }
    }
    
    while (!L1.empty())
    {
        L.push(L1.top());
        L1.pop();
    }

    while (!L2.empty())
    {
        L.push(L2.top());
        L2.pop();
    }

    for (auto & t : L) {
        std::cout<<t.cof<<", "<<t.exr<<std::endl;
    }

    return 0;
}