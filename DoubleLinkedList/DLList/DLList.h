#include <cstdarg>
#include <iostream>
#include <vector>

/****************************
*       Node
*    增加一个freq域，int类型
****************************/
template<class T> class DLList;
template<class T>
class Node {
	friend class DLList<T>;
private:
	T data;
	int freq;
	Node<T>* pre;
	Node<T>* next;

public:
	Node():
		data(), freq(), pre(nullptr), next(nullptr)
	{}

	Node(const T& data, Node<T>* pre, Node<T>* next, int freq=0) :
		data(data), pre(pre), next(next), freq(freq)
	{}

	const int& getFreq() {
		return freq;
	}

	const T& getData() {
		return data;
	}
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

	DLList(int len, ...);

	~DLList();

	void assignFreq(int cnt, ...);

	void printAll_and_Freq();

	const int& getLength() {
		return length;
	}

	void printAll();

	void printAll_to_Vector(std::vector<T>& vec);

	/*
	* 每进行一次此操作，具有元素值x的结点（假定表中元素值唯一）的freq加一，
	* 并使表中结点按freq值递减排序，最近访问过的结点排在具有相同freq值的结点的前面，
	*（假定初始有序且遵循此要求，初始状态就设为所有freq全0，那么只需要确定刚刚被访问的结点的插入位置）。
	*/
	Node<T>* locate(const T& x);
};

template<class T>
inline DLList<T>::DLList(int len, ...) :
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

template<class T>
inline DLList<T>::~DLList() {
	Node<T>* p = head;
	Node<T>* temp = nullptr;
	while (p) {
		temp = p->next;
		if (p)
			delete p;
		p = temp;
	}
}

template<class T>
inline void DLList<T>::assignFreq(int cnt, ...) {
	if (cnt > length || cnt < 1)
		return;
	va_list vaList;
	va_start(vaList, cnt);
	Node<T>* p = head->next;
	for (int i = 0; i <= cnt - 1; ++i) {
		if (p) {
			p->freq = va_arg(vaList, T);
			p = p->next;
		}
	}
	va_end(vaList);
}

template<class T>
inline void DLList<T>::printAll_and_Freq() {
	printAll();
	Node<T>* p = head->next;
	while (p) {
		if (p->next != nullptr)
			std::cout << p->freq << ",";
		else
			std::cout << p->freq << std::endl;
		p = p->next;
	}
	std::cout << std::endl;
}

template<class T>
inline void DLList<T>::printAll() {
	Node<T>* p = head->next;
	while (p) {
		if (p->next != nullptr)
			std::cout << p->data << ",";
		else
			std::cout << p->data << std::endl;
		p = p->next;
	}
}

template<class T>
inline void DLList<T>::printAll_to_Vector(std::vector<T>& vec) {
	Node<T>* p = head->next;
	while (p) {
		vec.push_back(p->data);
		p = p->next;
	}
}

/*
* 每进行一次此操作，具有元素值x的结点（假定表中元素值唯一）的freq加一，
* 并使表中结点按freq值递减排序，最近访问过的结点排在具有相同freq值的结点的前面，
*（假定初始有序且遵循此要求，初始状态就设为所有freq全0，那么只需要确定刚刚被访问的结点的插入位置）。
*/
template<class T>
inline Node<T>* DLList<T>::locate(const T& x) {
	Node<T>* p = head->next;
	while (p)
	{
		if (p->data == x)
			break;
		p = p->next;
	}
	if (p == nullptr)//无具有x元素值的结点
		exit(-1);
	else {//p指向被访问结点，下面寻找插入位置
		++p->freq;
		Node<T>* insertPos = head->next;
		while (insertPos != p) {
			if (insertPos->freq <= p->freq) {//<=
											 //摘出，插入新位置
				if (p->pre)
					p->pre->next = p->next;
				if (p->next)
					p->next->pre = p->pre;

				p->pre = insertPos->pre;
				insertPos->pre = p;
				p->pre->next = p;
				p->next = insertPos;
				return p;
			}
			else {
				insertPos = insertPos->next;
			}
		}//只可能往前插，从这里返回表示还是排在原来位置，不用摘出、插入。
		return p;
	}
}
