#include <cstdarg>
#include <iostream>
#include <vector>


template<class T> class CDLList;
template<class T>
class Node {
//public://ʡȥһЩ���ڷ���Ȩ�޵����飺����Node����Ԫ�� or public�ӿڷ���private��Ա
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
* �����Ƿ��ͷ�ڵ㣬�ɷ�Ϊ����List�࣬
* ����˫ѭ������nearָ�벻��Ҫ����Ϊͷָ����ǰ�ƶ�һ��λ�þ�ָ����β���
*********************************************************************/

/*******************************
*        CDLList
*		Ĭ�ϴ�ͷ���
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
		//β��
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
