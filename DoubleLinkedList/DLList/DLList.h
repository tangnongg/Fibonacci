#include <cstdarg>
#include <iostream>
#include <vector>

/****************************
*       Node
****************************/
template<class T> class DLList;
template<class T>
class Node {
	friend class DLList<T>;
private:
	T data;
	Node<T>* pre;
	Node<T>* next;

public:
	Node():
		data(), pre(nullptr), next(nullptr)
	{}

	Node(const T& data, Node<T>* pre, Node<T>* next) :
		data(data), pre(pre), next(next)
	{}
};

/****************************
*       DLList(带头结点)
****************************/
template<class T>
class DLList {
private:
	Node<T>* head;
	int length;

public:
	DLList() :
		head(new Node<T>), length(0)
	{}

	DLList(int len, ...) :
		head(new Node<T>), length(0) 
	{
		va_list vaList;
		va_start(vaList, len);
		Node<T>* rear = head;
		for (int i = 0; i <= len - 1; ++i) {
			Node<T>* newNode = new Node<T>(va_arg(vaList, T), rear, nullptr);
			rear->next = newNode;
			rear = newNode;
			++length;
		}		
		va_end(vaList);
	}

	~DLList() {
		Node<T>* p = head;
		Node<T>* temp = nullptr;
		while (p) {
			temp = p->next;
			if (p)
				delete p;
			p = temp;
		}
	}

	const int& getLength() {
		return length;
	}

	void printAll() {
		Node<T>* p = head->next;
		while (p) {
			if (p->next != nullptr)
				std::cout << p->data << ",";
			else
				std::cout << p->data << std::endl;
			p = p->next;
		}
	}

	void printAll_to_Vector(std::vector<T>& vec) {
		Node<T>* p = head->next;
		while (p) {
			vec.push_back(p->data);
			p = p->next;
		}
	}
};
