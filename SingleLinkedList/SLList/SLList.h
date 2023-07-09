#pragma once
#include <cstdarg>
#include <stack>
#include <vector>
#include <iostream>

//��ǰ����
template <class T> class SLList_without_HN;
template <class T> class SLList;

template <class T>
class Node {
	//����Node����Ԫ��Ϊ�˿�����Node����Ԫ��ֱ�ӷ���Node��protected��private��Ա
	friend class SLList_without_HN<T>;
	friend class SLList<T>;
private:
	T data;
	Node* next;

public:
	Node() :
	data(), next(nullptr)
	{}

	Node(const T& data, Node<T>* next) :
		data(data), next(next) 
	{}

	/*
	* ������������������ǽ���������һ����㣨����������next��Ϊnull����
	* ����Ҫ��ͨ������������ֻ�ͷŵ�ǰ�����ڴ棬��ȥ�ܵ�ǰ�����next���ӵ��ڴ档
	*/
	//~Node() {
	//	if (next)
	//		delete next;
	//}

	const T& getData() {
		return data;
	}
	//note:const Node<T>*& getNext() 
	//would lead to the problem:the pointer of const type* cant initialize the pointer of type*
	Node<T>*& getNext() {
		return next;
	}
};

/*************************
* �����Ƿ��ͷ�ڵ㣬�Ƿ��βָ��,�ɷ�Ϊ�ĸ�List��
**************************/


/*******************************
*        SLList
* Ĭ�ϴ�ͷ��㣬��βָ��
********************************/
template <class T>
class SLList {
private:
	Node<T>* head;
	int length;

public:
	SLList() :
		length(0), head(new Node<T>)
	{}

	SLList(int length, ...);

	~SLList();

	const int& getLength() {
		return length;
	}

	Node<T>*& getHead() {
		return head;
	}

	void printAll_to_Vector(std::vector<T>& vec);

	void SLList<T>::printAll();

	const T& getData(int pos);

	void deleteAllValue_x(T x);

	void printAllReversely();

	/*
	* if the minimum element is the unique one in the list, delete the element that first appears.
	*/
	void deleteMin();

	/*
	* ԭ�����ã���ͷ���
	*/
	void reverse();

	/*
	* ԭ�����򣬴�ͷ��㡣
	* ����ԭ�����õ�ʵ�֣�����������ʹ��ű���ֱ�Ӳ�������
	* order=0 for sorting in ascending order
	*/
	void insertSort(bool order = 0);

	void deleteAllValue_between_a_and_b(const T& a, const T& b);

	Node<T>* commonNode(SLList<T>& list);

	void emerge(SLList<T>& list);

	/*
	* �����������Ԫ�أ����ͷŽ�㣬��ʹ�ø����ռ��������
	* ���������У�����׽������������Ԫ��ֵ��ͬʱ�ͷŵ�ǰ��㡣
	*/
	void print_and_Realease();

	/*
	* �ֽ����������ԭ�����������Ϊ�����Ľ�㣬���صı������Ϊż���Ľ�㣬����Ԫ�����˳�򲻱䡣
	* ��ż����ŵĽ��ժ����׷�ӣ�β�壩�����ر���
	* ����1:��ǰ׼������һ�ֵġ�����ָ���顰�ŵ��������顱�����ֵĽ�����ȡ�á������顱��
	* ����2��count������ǰ������š�
	*/
	void divide_into_Two(SLList<T>& retList);


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

	~SLList_without_HN();

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

	Node<T>* rear = head;//��¼β��㣬����ÿ��β�嶼Ҫ������β��㡣
	for (int i = 0; i < length; ++i) {
		Node<T>* newNode = new Node<T>;
		newNode->data = va_arg(vaList, T);
		newNode->next = nullptr;
		//��Ϊû��ͷ��㣬�Ա�ͷ�Ĳ�����ͳһ����Ҫ�������ǡ�
		if (rear)//���ǿձ���rear->next���е�near��Ϊ��
			rear->next = newNode;
		else//�ǿձ���
			head = newNode;
		rear = newNode;
	}

	va_end(vaList);
}

template<class T>
inline SLList_without_HN<T>::~SLList_without_HN() {
	Node<T>* p = head;
	if (p) {
		Node<T>* temp = p;
		p = p->next;
		if (temp)
			delete temp;
	}
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
	//Ҫɾ����㣬����˫ָ�뷨������ָ��������ǰ����ָ�롣
	//��ͷ��㣺��ΪҪά��˫ָ���λ�ã������˶Ա�ͷ�Ĵ�����
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
	//��Ϊ��ͷ��㣬���Ա�ͷ���д���
	if (head->data == x) {
		Node<T>* temp = head;
		head = head->next;
		if (temp)
			delete temp;
	}
}

template<class T>
inline void SLList_without_HN<T>::deleteAllValue_x_Recursive(Node<T>*& head, T x) {
	//��ֹ����
	if (!head)
		return;
	//��С��ģ����ͬ����
	deleteAllValue_x_Recursive(head->next, x);
	//����������
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
	this->length = length;
	va_list vaList;
	va_start(vaList, length);

	//������һ��ͷ���
	head = new Node<T>;
	Node<T>* rear = head;
	for (int i = 0; i <= length - 1; ++i) {
		Node<T>* newNode = new Node<T>(va_arg(vaList, T), nullptr);
		rear->next = newNode;
		rear = newNode;
	}
	va_end(vaList);
}

template<class T>
inline SLList<T>::~SLList() {
	Node<T>* p = head;
	if (p) {
		Node<T>* temp = p;
		p = p->next;
		if (temp)
			delete temp;
	}
}

template<class T>
inline void SLList<T>::printAll_to_Vector(std::vector<T>& vec) {
	//Node<T>* p = head;
	//while (p) {
	//	p = p->next;
	//	if(p)//����Ұָ�룬��ָ��ᷢ���쳣 access vialation
	//		vec.push_back(p->data);
	//}
	Node<T>* p = head->next;
	while (p) {
		vec.push_back(p->data);
		p = p->next;
	}
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
inline const T& SLList<T>::getData(int pos) {
	//����г�Աlength��ֱ�Ӱ�pos��length���Ƚ�
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
	--length;
}

/*
* ԭ�����ã���ͷ���
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
* ԭ�����򣬴�ͷ��㡣
* ����ԭ�����õ�ʵ�֣�����������ʹ��ű���ֱ�Ӳ�������
*/
template<class T>
inline void SLList<T>::insertSort(bool order) {
	Node<T>* p = head->next;//�������ָ��������unorderedList
	head->next = nullptr;//ǰ��head,β��������β
	Node<T>* unorderedList = nullptr;//���unorderedList

	while (p) {
		unorderedList = p->next;

		//Ѱ�ҹ���������������"����λ��"�����ڸ�Ԫ��֮ǰ����Ҫǰ����
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

		p = unorderedList;
	}
}

template<class T>
inline void SLList<T>::deleteAllValue_between_a_and_b(const T& a, const T& b) {
	if (a > b)
		return;
	Node<T>* pre = head;
	Node<T>* p = head->next;
	while (p) {
		if (p->data >= a && p->data <= b) {
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
inline Node<T>* SLList<T>::commonNode(SLList<T>& list) {
	int diff = std::abs(length - list.getLength());
	Node<T>* p = head;
	Node<T>* listP = list.getHead();
	for (int i = 0; i <= diff - 1; ++i) {
		p = p->next;
	}
	while (p) {
		if (p == listP) {
			return p;
		}
		else {
			p = p->next;
			listP = listP->next;
		}
	}
	//return nullptr;
}

template<class T>
inline void SLList<T>::emerge(SLList<T>& list) {
	Node<T>* p = head;
	while (p->next) {//get the pointer to the rear node.
		p = p->next;
	}
	p->next = list.getHead()->getNext();//list��ͷ����������list����
	length += list.getLength();
}

/*
* �����������Ԫ�أ����ͷŽ�㣬��ʹ�ø����ռ��������
* ���������У�����׽������������Ԫ��ֵ��ͬʱ�ͷŵ�ǰ��㡣
*/
template<class T>
inline void SLList<T>::print_and_Realease() {
	insertSort(0);
	Node<T>* p = head->next;
	head->next = nullptr;//if not to do this, it will become a wild pointer(its space is freed but it is not nullptr).
	while (p) {
		if (p->next == nullptr) {
			std::cout << p->data << std::endl;
			if (p)
				delete p;
			--length;
			return;
		}
		std::cout << p->data << ",";
		Node<T>* temp = p;
		p = p->next;
		if (temp)
			delete temp;
		--length;
	}
}

/*
* �ֽ����������ԭ�����������Ϊ�����Ľ�㣬���صı������Ϊż���Ľ�㣬����Ԫ�����˳�򲻱䡣
* ��ż����ŵĽ��ժ����׷�ӣ�β�壩�����ر���
*/
template<class T>
inline void SLList<T>::divide_into_Two(SLList<T>& retList) {
	Node<T>* rear = retList.getHead();
	Node<T>* pre = head->next;
	Node<T>* p = nullptr;
	if (pre)
		p = pre->next;
	else
		return;
	static Node<T>* nextPre = nullptr;
	Node<T>* nextP = nullptr;
	//�����ǳ�ʼ״̬��ѡȡ
	while (p) {
		//׼�����֣�����
		nextP = p->next;
		nextPre = pre->next;
		if (nextP) {
			nextP = nextP->next;
			nextPre = nextPre->next;
		}
		//ժȡ
		pre->next = p->next;
		//β��׷��
		p->next = nullptr;
		rear->next = p;
		rear = p;
		//ȡ�ñ���
		pre = nextPre;
		p = nextP;
	}
}

