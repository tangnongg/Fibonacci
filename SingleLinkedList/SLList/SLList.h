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

	/*����Ľӿڲ��Ǳ�Ҫ�ģ���Ϊ�Ѿ���Node��������List��������Ԫ�࣬��List�п���ֱ�ӷ���Node��private��protected��Ա*/
	const T& getData() {
		return data;
	}
	//note:const Node<T>*& getNext() 
	//would lead to the problem:the pointer of const type* cant initialize the pointer of type*
	Node<T>*& getNext() {
		return next;
	}
};

/***********************************************
* �����Ƿ��ͷ�ڵ㣬�Ƿ��βָ��,�ɷ�Ϊ�ĸ�List��
************************************************/


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

	void setLength(int len) {
		length = len;
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
	void reverse(Node<T>* head);

	/*
	* ԭ�����򣬴�ͷ��㡣
	* ����ԭ�����õ�ʵ�֣����������ʹ��ű�ֱ�Ӳ�������
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
	* �ֽ��������ԭ�����������Ϊ�����Ľ�㣬���صı�retList�����Ϊż���Ľ�㣬����Ԫ�����˳�򲻱䡣
	* divide {a1,b1,a2,b2,...,an,bn} into {a1,a2,...,an} and {b1,b2,...,bn}
	* ˼·����ż����ŵĽ��ժ����׷�ӣ�β�壩�����ر�
	* ����1:��ǰ׼������һ�ֵġ�����ָ���顰�ŵ��������顱�����ֵĽ�����ȡ�á������顱��
	* ����2��count������ǰ������š�
	*/
	void divide_into_Two(SLList<T>& retList);

	/*
	* divide {a1,b1,a2,b2,...,an,bn} into {a1,a2,...,an} and {bn,...b2,b1}
	* ˼·����ż����ŵĽ��ժ����ǰ�ã�ͷ�壩�����ر�
	* note:         temp------>data|next
	*                              ^
	*							   |
	*                              p
	*       Because they are the same piece of space, temp->next varies along with p->next. 
	*/
	void divide_into_Two_2(SLList<T>& retList);

	/*
	* "���������"������ȥ����ֵ��ͬ��Ԫ�أ�ʹ���в������ظ���Ԫ�ء�
	*/
	void beingNoSameElement();

	/*
	* ���������ĵ�����ϲ���һ���ݼ��ĵ�����
	* Ҫ������ԭ���Ľ����Ϊ�ϲ��������Ľ�㡣
	* ��������������ָ��ֱ�ָ����������׽�㣬�Ƚ����ǵ�ǰ��ָ����������Ԫ��ֵ��
	* ��ԭ���������ɽ���+��ͷ�巨��-->ȡMin������ģ�⣬����ȷ����
	*/
	void emergetoNewList(SLList<T>& list);

	/*
	* ����һ���µľ���������������Ԫ��ֵΨһ���Ĺ���Ԫ��ֵ������, ���ƻ�ԭ��������
	* ���������generatedList
	*/
	void generateCommonVlaueList(SLList<T>& list, SLList<T>& generatedList);

	/*
	* ����һ���µľ���������������Ԫ��ֵΨһ���Ĺ���Ԫ��ֵ������, ����ԭ��������Ľ�㡣
	* ��������ڵ�ǰ����
	*/
	void generateCommonVlaueList(SLList<T>& list);

	/*
	* �Ƿ���������У�i.e. mode match.
	* ѭ�����
	*/
	bool modeMatch(SLList<T>& modeList);

	/*
	* �Ƿ�(β��)�л�
	* ����ָ��˼��
	*/
	bool is_with_a_Loop();

	/*
	* 408����
	* ��ȡ����������K������Ԫ�� 
	* ret:false for failure��true for having the Kth node from the bottom, retValue is the target value.
	*/
	bool gettheKth_fromtheBottom(T& retVlaue, int k);

	/*
	* 408����
	* |data|<=n, ��data����������ʹ�����޾���ֵ��ͬ��Ԫ��,������һ�γ��ֵġ�
	*/
	void beingNoElement_withSameAbsValue(int n);

	/*
	* 408����
	* {a1,a2,a3,...,an-1,an} --> {a1,an,a2,an-1,a3...}
	*/
	void rearrange();
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
		if (rear)//���ǿձ�rear->next���е�near��Ϊ��
			rear->next = newNode;
		else//�ǿձ�
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
	//��ͷ��㣺��ΪҪά��˫ָ���λ�ã������˶Ա�ͷ�Ĵ���
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
	//���������
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

template<class T>
inline void SLList<T>::reverse(Node<T>* head) {
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
* ����ԭ�����õ�ʵ�֣����������ʹ��ű�ֱ�Ӳ�������
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
	return nullptr;//�޹������
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
* �ֽ��������ԭ�����������Ϊ�����Ľ�㣬���صı�retList�����Ϊż���Ľ�㣬����Ԫ�����˳�򲻱䡣
* ��ż����ŵĽ��ժ����׷�ӣ�β�壩�����ر�
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
		--length;
		retList.setLength(retList.getLength() + 1);
		//ȡ�ñ���
		pre = nextPre;
		p = nextP;
	}
}

/*
* divide {a1,b1,a2,b2,...,an,bn} into {a1,a2,...,an} and {bn,...b2,b1}
* ˼·����ż����ŵĽ��ժ����ǰ�ã�ͷ�壩�����ر�
* note:         temp------>data|next
*                              ^
*							   |
*                              p
*       Because they are the same piece of space, temp->next varies along with p->next.
*/
template<class T>
inline void SLList<T>::divide_into_Two_2(SLList<T>& retList) {
#if 0
	divide_into_Two(retList);
	retList.reverse();
#else
	int count = 1;
	Node<T>* p = head->next;
	Node<T>* pre = head;
	while (p) {
		if (count % 2 == 0) {
			pre->next = p->next;

			p->next = retList.getHead()->getNext();
			retList.getHead()->getNext() = p;

			p = pre->next;

			--length;
			retList.setLength(retList.getLength() + 1);
		}
		else {
			pre = pre->next;
			p = p->next;
		}
		++count;
	}
#endif
}

/*
* "���������"������ȥ����ֵ��ͬ��Ԫ�أ�ʹ���в������ظ���Ԫ�ء�
*/
template<class T>
inline void SLList<T>::beingNoSameElement() {
	Node<T>* pre = head->next;
	Node<T>* p = nullptr;
	if (pre)
		p = pre->next;
	else
		return;
	Node<T>* stagedPNext = nullptr;
	Node<T>* stagedPreNext = nullptr;
	while (p) {
		if (p->data == pre->data) {
			p = p->next;//ĩβ������ȵ����
		}
		else {
			stagedPNext = p->next;
			stagedPreNext = pre->next;

			pre->next = p;
			pre = p;
			p = p->next;

			stagedPreNext = nullptr;
			while (stagedPreNext) {
				delete stagedPreNext;
				--length;
				stagedPreNext = stagedPreNext->next;
			}
		}
	}
	//in case ĩβ������ȵ����
	p = pre->next;
	pre->next = nullptr;
	while (p) {
		Node<T>* temp = p;
		p = p->next;
		delete temp;
		--length;
	}
}

/*
* ���������ĵ�����ϲ���һ���ݼ��ĵ�����
* Ҫ������ԭ���Ľ����Ϊ�ϲ��������Ľ�㡣
* ��������������ָ��ֱ�ָ����������׽�㣬�Ƚ����ǵ�ǰ��ָ����������Ԫ��ֵ��
* ��ԭ���������ɽ���+��ͷ�巨��-->ȡMin������ģ�⣬����ȷ����
*/
template<class T>
inline void SLList<T>::emergetoNewList(SLList<T>& list) {
	Node<T>* p = head->next;
	Node<T>* listP = list.getHead()->getNext();
	head->next = nullptr;
	Node<T>* min = nullptr;
	while (p && listP)
	{
		if (p->data >= listP->data) {
			min = listP;
			listP = listP->next;
		}
		else {
			min = p;
			p = p->next;
		}
		min->next = head->next;
		head->next = min;
	}
	Node<T>* temp = nullptr;
	if (!p) {
		while (listP) {
			temp = listP->next;//note: Ŀ�ľ���listP->next,ֱ��copy��������listP����ֹ���汻���ˡ�
			listP->next = head->next;//��ֹ���汻���ˣ�������ָ�˴�
			head->next = listP;
			listP = temp;
		}
	}
	else {
		while (p) {
			temp = p->next;
			p->next = head->next;
			head->next = p;
			p = temp;
		}
	}
	length += list.getLength();
}

/*
* ����һ���µľ���������������Ԫ��ֵΨһ���Ĺ���Ԫ��ֵ������, ���ƻ�ԭ��������
*/
template<class T>
inline void SLList<T>::generateCommonVlaueList(SLList<T>& list, SLList<T>& generatedList) {
	Node<T>* p = head->next;
	Node<T>* listP = list.getHead()->getNext();
	Node<T>* rear = generatedList.getHead();
	while (p) {
		while (listP) {
			if (listP->data == p->data) {
				Node<T>* newNode = new Node<T>(listP->data, nullptr);
				listP = listP->next;//��θ��¿��Լ���һ������ıȽ�
				rear->getNext() = newNode;
				rear = newNode;
				generatedList.setLength(generatedList.getLength() + 1);
				break;
			}
			else if (listP->data < p->data)
			{
				listP = listP->next;
			}
			else {
				break;
			}
		}
		p = p->next;
	}
}

/*
* ����һ���µľ���������������Ԫ��ֵΨһ���Ĺ���Ԫ��ֵ������, ����ԭ��������Ľ�㡣
* ��������ڵ�ǰ����
*/
template<class T>
inline void SLList<T>::generateCommonVlaueList(SLList<T>& list) {
	Node<T>* p = head->next;
	Node<T>* pre = head;//ʹ��ժȡ������������������Ȼ�����������ͷš�
	Node<T>* listP = list.getHead();
	Node<T>* newHeadNode = new Node<T>;//������������ӵ�������֮��
	int insertCnt = 0;
	while (listP) {
		while (p) {
			if (p->data == listP->data) {
				pre->next = p->next;
				Node<T>* temp = p->next;//copyֱ��Ŀ�꣬�����ں���ı���������б��۸�

				p->next = newHeadNode->next;
				newHeadNode->next = p;

				p = temp;//update,��ͬ����һ�����⣬��������ժȡ����
				++insertCnt;
				break;
			}
			else if (p->data < listP->data) {
				p = p->next;
				pre = pre->next;
			}
			else {
				break;
			}
		}
		listP = listP->next;
	}
	p = head->next;
	while (p) {
		Node<T>* temp = p->next;
		delete p;
		p = temp;
	}
	head->next = newHeadNode->next;
	if (newHeadNode)
		delete newHeadNode;
	length = insertCnt;
}

/*
* �Ƿ���������У�i.e. mode match.
* ѭ�����
*/
template<class T>
inline bool SLList<T>::modeMatch(SLList<T>& modeList) {
	Node<T>* nextP = head->next;
	Node<T>* p = nextP;
	Node<T>* modeListP = modeList.getHead()->getNext();
	//while(nextP){ while(p && modeListP) {...} } ,
	//note:ֻҪһ��ѭ�����㹻������p����nextP������ֻҪnextP��Ϊnull, nextP�Ͳ���Ϊnull���������������ˡ�
	while (p && modeListP) {//���ͬ�����ƣ����ȡ���ԭ����
		if (p->data == modeListP->data)
		{
			p = p->next;
			modeListP = modeListP->next;
		}
		else {
			p = nextP->next;
			nextP = nextP->next;
			modeListP = modeList.getHead()->getNext();
		}
	}
	if (!p) {
		return false;
	}
	else {
		return true;
	}
}

/*
* �Ƿ�(β��)�л�
* ����ָ��˼��
*/
template<class T>
inline bool SLList<T>::is_with_a_Loop() {
	Node<T>* slow = head;
	Node<T>* quick = head->next;
	while (quick && slow != quick) {
		quick = quick->next;
		if (quick)
			quick = quick->next;
		else
			return false;
		slow = slow->next;
	}
	if (!quick)
		return false;
	else//slow�ڻ���Ż�׷��quick
		return true;
}

/*
* 408����
* ��ȡ����������K������Ԫ��
* ret:false for failure��true for having the Kth node from the bottom, retValue is the target value.
*/
template<class T>
inline bool SLList<T>::gettheKth_fromtheBottom(T& retVlaue, int k) {
	Node<T>* front = head->next;
	Node<T>* behind = head->next;
	while (k) {
		if (!front)
			return false;
		front = front->next;
		--k;
	}
	//at the moment, behind=head->next, behind lags behind front k nodes, unknowing front is nullptr or not.
	while (front) {
		front = front->next;
		behind = behind->next;
	}
	retVlaue = behind->data;
	return true;
}

/*
* 408����
* |data|<=n, ��data����������ʹ�����޾���ֵ��ͬ��Ԫ��,������һ�γ��ֵġ�
*/
template<class T>
inline void SLList<T>::beingNoElement_withSameAbsValue(int n) {
	volatile bool* flagArr = new bool[n + 1];
	for (int i = 0; i <= n; ++i) {
		flagArr[i] = false;
	}
	Node<int>* p = head->next;
	Node<int>* pre = head;
	Node<int>* temp = nullptr;
	while (p) {
		int abs = std::abs(p->data);
		if (flagArr[abs] == false) {
			flagArr[abs] = true;
			p = p->next;
			pre = pre->next;
		}
		else {
			pre->next = p->next;
			temp = p;
			p = p->next;
			delete temp;
		}
	}
}

/*
* 408����
* {a1,a2,a3,...,an-1,an} --> {a1,an,a2,an-1,a3...}
*/
template<class T>
inline void SLList<T>::rearrange() {
	Node<T>* pFormerLs = head->next;
	Node<T>* pLaterLs = nullptr;//ǰ����������Ҫ������
	Node<T>* pLaterLsPre = head;
	int halfNum = (length + 1) / 2;//��ǰ�������̣��ŵ㣺ÿ������㶼�ᱻ���뵽ǰ������ͳһ������Ҫ��������жϡ�
	halfNum;//pLaterLsPre��head�ƶ�������ͷ�����������		
	while (halfNum)
	{
		pLaterLsPre = pLaterLsPre->next;
		--halfNum;
	}
	reverse(pLaterLsPre);
	pLaterLs = pLaterLsPre->next;
	pLaterLsPre->next = nullptr;
	while (pLaterLs) {
		Node<T>* nextPLaterLs = pLaterLs->next;
		pLaterLs->next = pFormerLs->next;
		pFormerLs->next = pLaterLs;

		pLaterLs = nextPLaterLs;
		pFormerLs = pFormerLs->next->next;//ǰ��ֻ��������ض���Ϊnullptr
	}
}


