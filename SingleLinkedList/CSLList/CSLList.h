#include <iostream>
#include <cstdarg>
#include <vector>

/********************************************
*			结点的定义
*********************************************/
template<class T> class CSLList;
template<class T>
class Node {
	friend class CSLList<T>;
private:
	T data;
	Node<T>* next;

public:
	Node():
		data(), next(nullptr)
	{}

	Node(const T& data, Node<T>* next):
		data(data), next(next)
	{}
};


/********************************************
* 带头结点，不带尾指针的循环单链表（by default)
*********************************************/
template<class T> class CSLList;
template<class T>
class CSLList{
	friend class CSLList<T>;
private:
	Node<T>* head;
	int length;

public:
	CSLList():
		head(new Node<T>), length(0)
	{
		head->next = head;
	}

	CSLList(int length, ...);

	~CSLList();

	const int& getLength() {
		return length;
	}

	void printAll();

	void printAll_to_Vector(std::vector<T>& vec) {
		Node<T>* p = head->next;
		while (p != head) {
			vec.push_back(p->data);
			p = p->next;
		}
	}

	/*
	* 将另一个表链接到该表之后
	*/
	void emerge(CSLList<T>& list);

	/*
	* 反复删除元素值最小的结点
	* method 1:每次找最小，输出后删除；(每次不破环原来的相对顺序）
	* method 2：先排序，依次输出后删除
	*/
	void deleteMinRepeatly(std::vector<T>& vec) {
		while (head->next != head) {
			vec.push_back(deleteMin());
		}
	}

	/*
	* 找最小，输出(作为返回值）后删除
	*/
	T deleteMin() {
		Node<T>* p = head->next;
		Node<T>* pre = head;
		Node<T>* min = head->next;
		Node<T>* minPre = head;
		while (p!=head) {
			if (p->data < min->data) {
				min = p;
				minPre = pre;
			}
			p = p->next;
			pre = pre->next;
		}
		minPre->next = min->next;
		Node<T> temp = *min;
		if (min)
			delete min;
		--length;
		return temp.data;
	}
};

template<class T>
inline CSLList<T>::CSLList(int length, ...) :
	head(new Node<T>), length(0)
{
	head->next = head;

	va_list vaList;
	va_start(vaList, length);
	Node<T>* rear = head;
	for (int i = 0; i <= length - 1; ++i) {
		Node<T>* newNode = new Node<T>(va_arg(vaList, T), rear->next);//尾结点的next处不可直接用nullptr了
		rear->next = newNode;
		rear = newNode;
		++this->length;
	}
	va_end(vaList);
}

template<class T>
inline CSLList<T>::~CSLList() {
	Node<T>* p = head->next;
	Node<T>* temp = nullptr;
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
inline void CSLList<T>::printAll() {
	Node<T>* p = head->next;
	while (p != head) {
		if (p->next != head)
			std::cout << p->data << ",";
		else
			std::cout << p->data << std::endl;
		p = p->next;
	}
}

/*
* 将另一个表链接到该表之后
*/
template<class T>
inline void CSLList<T>::emerge(CSLList<T>& list) {
	Node<T>* rear = head;
	while (rear->next != head)
		rear = rear->next;

	Node<T>* listRear = list.head;
	while (listRear->next != list.head)
		listRear = listRear->next;

	rear->next = list.head->next;
	listRear->next = head;

	list.head->next = list.head;
	length += list.length;
	list.length = 0;
}
