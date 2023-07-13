#include <cstdarg>
#include <iostream>
#include <vector>


template<class T> class CDLList;
template<class T>
class Node {
//public://省去一些关于访问权限的事情：声明Node的友元类 or public接口访问private成员
	friend class CDLList<T>;
private:
	T data;
	Node<T>* next;
	Node<T>* pre;

public:
	Node() :
		data(), next(nullptr), pre(nullptr)
	{}

	Node(const T& data, Node<T>* next, Node<T>* pre) :
		data(), next(next), pre(pre)
	{}
};


/******************************************************************
* 根据是否带头节点，可分为两个List类，
* 对于双循环链表，near指针不必要，因为头指针向前移动一个位置就指向了尾结点
*********************************************************************/

/*******************************
*        CDLList
*		默认带头结点
********************************/
template<class T> class CDLList;
template<class T>
class CDLList {
	friend class CDLList<T>;
private:
	Node<T>* head;
	int length;

public:
	CDLList();

	CDLList(int length, ...);

	~CDLList();

	int getLength();

	void printAll();

	void printAll_to_Vector(std::vector<int>& vec) {
		Node<T>* p = head->next;
		while (p != head) {
			vec.push_back(p->data);
			p = p->next;
		}
	}

	bool isSymmetrical() {
		Node<T>* low = head->next;
		Node<T>* high = head->pre;
		while (high->next!=low && high!=low)
		{
			if (low->data != high->data)
				return false;
			low = low->next;
			high = high->pre;
		}
		return true;
	}
};

template<class T>
inline CDLList<T>::CDLList() :
	head(new Node<T>), length()
{
	head->next = head;
	head->pre = head;
}

template<class T>
inline CDLList<T>::CDLList(int length, ...)
{
	this->length = 0;
	head = new Node<T>;
	head->next = head;
	head->pre = head;

	va_list vaList;
	va_start(vaList, length);
	for (int i = 0; i <= length - 1; ++i) {
		Node<T>* newNode = new Node<T>;
		newNode->data = va_arg(vaList, T);
		//尾插
		newNode->pre = head->pre;
		head->pre = newNode;
		newNode->next = head;
		newNode->pre->next = newNode;

		++this->length;
	}
	va_end(vaList);
}

template<class T>
inline CDLList<T>::~CDLList() {
	Node<T>* p = head->next;
	Node<T>* temp = new Node<T>;
	while (p != head) {
		temp = p->next;
		if (p)
			delete p;
		p = temp;
	}
	if (head)
		delete head;
}

template<class T>
inline int CDLList<T>::getLength() {
	return length;
}

template<class T>
inline void CDLList<T>::printAll() {
	Node<T>* p = head->next;
	while (p != head) {
		if (p->next != head)
			std::cout << p->data << ",";
		else {
			std::cout << p->data << std::endl;
		}
		p = p->next;
	}
}
