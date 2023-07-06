#pragma once
#include <cstdarg>
#include <stack>

//类前声明
template <class T> class SLList_without_HN;
template <class T> class SLList;

template <class T>
class Node {
	//声明Node的友元，为了可以在Node的友元中直接访问Node的protected和private成员
	friend class SLList_without_HN<T>;
	friend class SLList<T>;
private:
	T data;
	Node* next;

public:
	Node() :
	next(nullptr)
	{}

	Node(const T& data, Node<T>* next) :
		data(data), next(next) 
	{}
};

/*************************
* 根据是否带头节点，是否带尾指针,可分为四个List类
**************************/


/*******************************
*        SLList
* 默认带头结点，无尾指针
********************************/
template <class T>
class SLList {
private:
	Node<T>* head;
	int length;

public:
	SLList() :
		head(nullptr), length(0)
	{}

	SLList(int length, ...);

	void SLList<T>::printAll();

	const T& getData(int pos) {
		Node<T>* p = head;
		for (int i = 0; i <= pos - 1; ++i) {
			if (!p) {
				std::cout << "acessing out of range!" << std::endl;
				exit(-1);
			}
			p = p->next;
		}
		if (!p) {
			std::cout << "acessing out of range!" << std::endl;
			exit(-1);
		}
		else {
			return p->data;
		}
	}

	void deleteAllValue_x(T x);

	void printAllReversely();

	/*
	* if the minimum element is the unique one in the list, delete the element that first appears.
	*/
	void deleteMin();

	/*
	* 原地逆置，带头结点
	*/
	void reverse();

	/*
	* 原地排序，带头结点。
	* 参照原地逆置的实现，看作有序表和待排表，直接插入排序
	*/
	void insertSort(bool order = 0);
};


/******************************
*      SLList_without_HN
*******************************/
template <class T>
class SLList_without_HN {
private:
	Node<T>* head;
	int length;
public:
	SLList_without_HN() :
		head(nullptr), length(0)
	{}

	SLList_without_HN(int length, ...);

	void printAll();

	void deleteAllValue_x(T x);

	void deleteAllValue_x_Recur(T x) {
		deleteAllValue_x_Recursive(head, x);
	}

	void deleteAllValue_x_Recursive(Node<T>*& head, T x);


};


/***************************************
*   implement of SLList_without_HN
***************************************/
template<class T>
inline SLList_without_HN<T>::SLList_without_HN(int length, ...) :
	head(nullptr), length(length)
{
	va_list vaList; 
	va_start(vaList, length);

	Node<T>* rear = head;//记录尾结点，避免每次尾插都要遍历到尾结点。
	for (int i = 0; i < length; ++i) {
		Node<T>* newNode = new Node<T>;
		newNode->data = va_arg(vaList, T);
		newNode->next = nullptr;
		//因为没有头结点，对表头的操作不统一，需要单独考虑。
		if (rear)//不是空表，rear->next其中的near不为空
			rear->next = newNode;
		else//是空表。
			head = newNode;
		rear = newNode;
	}

	va_end(vaList);
}

template<class T>
inline void SLList_without_HN<T>::printAll()
{
	Node<T>* p = head;
	while (p)
	{
		if (!(p->next)) {
			std::cout << p->data << std::endl;
			break;
		}
		std::cout << p->data << ",";
		p = p->next;
	}
}

template<class T>
inline void SLList_without_HN<T>::deleteAllValue_x(T x) {
	//要删除结点，采用双指针法，保留指向工作结点的前驱的指针。
	//无头结点：因为要维护双指针的位置，跳过了对表头的处理。
	if (!head)
		return;
	Node<T>* pre = head;
	Node<T>* p = head->next;
	while (p) {
		if (p->data == x) {
			pre->next = p->next;
			Node<T>* temp = p;
			p = p->next;	

			if (temp)
				delete temp;
			--length;
		}

		else {
			pre = pre->next;
			p = p->next;
		}
	}
	//因为无头结点，最后对表头进行处理
	if (head->data == x) {
		Node<T>* temp = head;
		head = head->next;
		if (temp)
			delete temp;
	}
}

template<class T>
inline void SLList_without_HN<T>::deleteAllValue_x_Recursive(Node<T>*& head, T x) {
	//终止条件
	if (!head)
		return;
	//更小规模的相同问题
	deleteAllValue_x_Recursive(head->next, x);
	//处理该问题
	if (head->data == x) {
		Node<T>* temp = head;
		head = head->next;
		if (temp)
			delete temp;
		--length;
	}
}


/**************************
*   implement of SLList
***************************/
template<class T>
inline SLList<T>::SLList(int length, ...) {
	va_list vaList;
	va_start(vaList, length);

	//先生成一个头结点
	head = new Node<T>;
	Node<T>* rear = head;
	for (int i = 0; i <= length - 1; ++i) {
		Node<T>* newNode = new Node<T>(va_arg(vaList, T), nullptr);
		rear->next = newNode;
		rear = newNode;
		++this->length;
	}

	va_end(vaList);
}

template<class T>
inline void SLList<T>::printAll()
{
	Node<T>* p = head->next;
	while (p)
	{
		if (!(p->next)) {
			std::cout << p->data << std::endl;
			break;
		}
		std::cout << p->data << ",";
		p = p->next;
	}
}

template<class T>
inline void SLList<T>::deleteAllValue_x(T x) {
	Node<T>* pre = head;
	Node<T>* p = head->next;
	while (p) {
		if (p->data == x) {
			pre->next = p->next;
			Node<T>* temp = p;
			p = p->next;

			if (temp)
				delete temp;
			--length;
		}
		else {
			pre = pre->next;
			p = p->next;
		}
	}
}

template<class T>
inline void SLList<T>::printAllReversely() {
	Node<T>* p = head->next;
	std::stack<T> stc;
	while (p) {
		stc.push(p->data);
		p = p->next;
	}
	while (!stc.empty()) {
		if (stc.size() == 1) {
			std::cout << stc.top() << std::endl;
			stc.pop();
			break;
		}
		std::cout << stc.top() << ",";
		stc.pop();
	}
}

/*
* if the minimum element is the unique one in the list, delete the element that first appears.
*/
template<class T>
inline void SLList<T>::deleteMin() {
	Node<T>* minPre, * min, * pre, * p;
	minPre = head; min = head->next;
	pre = head; p = head->next;
	while (p) {
		if (p->data < min->data) {
			min = p;
			minPre = pre;
		}
		p = p->next;
		pre = pre->next;
	}
	minPre->next = min->next;
	if (min)
		delete min;
}

/*
* 原地逆置，带头结点
*/
template<class T>
inline void SLList<T>::reverse() {
	Node<T>* p = head->next;
	head->next = nullptr;
	Node<T>* laterLs = nullptr;
	while (p) {
		laterLs = p->next;
		p->next = head->next;
		head->next = p;
		p = laterLs;
	}
}

/*
* 原地排序，带头结点。
* 参照原地逆置的实现，看作有序表和待排表，直接插入排序
*/
template<class T>
inline void SLList<T>::insertSort(bool order) {
	Node<T>* p = head->next;//这个工作指针遍历后表laterLs
	head->next = nullptr;//前表head,尾部断链结尾
	Node<T>* laterLs = nullptr;//后表laterLs
	while (p) {
		laterLs = p->next;

		//寻找工作结点在有序表中"插入位置"。插在该元素之前，需要前驱。
		Node<T>* insertPosPre = head;
		Node<T>* insertPos = head->next;
		while (insertPos) {
			if (order == 0) {//sort in ascending order
				if (p->data <= insertPos->data) {
					break;
				}
			}
			else {//sort in descending order
				if (p->data >= insertPos->data) {
					break;
				}
			}
			insertPosPre = insertPosPre->next;
			insertPos = insertPos->next;
		}
		p->next = insertPosPre->next;
		insertPosPre->next = p;

		p = laterLs;
	}
}


