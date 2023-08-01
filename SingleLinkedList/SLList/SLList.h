#pragma once
#include <cstdarg>
#include <stack>
#include <vector>
#include <iostream>

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
	data(), next(nullptr)
	{}

	Node(const T& data, Node<T>* next) :
		data(data), next(next) 
	{}

	/*
	* 会造成连环析构，而非仅仅析构这一个结点（如果这个结点的next不为null），
	* 就是要普通的析构函数，只释放当前结点的内存，不去管当前结点中next连接的内存。
	*/
	//~Node() {
	//	if (next)
	//		delete next;
	//}

	/*下面的接口不是必要的，因为已经在Node中声明了List是它的友元类，在List中可以直接访问Node的private，protected成员*/
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
* 根据是否带头节点，是否带尾指针,可分为四个List类
************************************************/


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
	* 原地逆置，带头结点
	*/
	void reverse();
	void reverse(Node<T>* head);

	/*
	* 原地排序，带头结点。
	* 参照原地逆置的实现，看作有序表和待排表，直接插入排序
	* order=0 for sorting in ascending order
	*/
	void insertSort(bool order = 0);

	void deleteAllValue_between_a_and_b(const T& a, const T& b);

	Node<T>* commonNode(SLList<T>& list);

	void emerge(SLList<T>& list);

	/*
	* 递增输出链表元素，并释放结点，不使用辅助空间的做法。
	* 先升序排列，后从首结点遍历输出结点的元素值，同时释放当前结点。
	*/
	void print_and_Realease();

	/*
	* 分解成两个表。原来表留下序号为奇数的结点，返回的表retList放序号为偶数的结点，保存元素相对顺序不变。
	* divide {a1,b1,a2,b2,...,an,bn} into {a1,a2,...,an} and {b1,b2,...,bn}
	* 思路：把偶数序号的结点摘出，追加（尾插）到返回表。
	* 方法1:提前准备好下一轮的”工作指针组“放到“备份组”，该轮的结束，取用“备份组”。
	* 方法2：count计数当前结点的序号。
	*/
	void divide_into_Two(SLList<T>& retList);

	/*
	* divide {a1,b1,a2,b2,...,an,bn} into {a1,a2,...,an} and {bn,...b2,b1}
	* 思路：把偶数序号的结点摘出，前置（头插）到返回表。
	* note:         temp------>data|next
	*                              ^
	*							   |
	*                              p
	*       Because they are the same piece of space, temp->next varies along with p->next. 
	*/
	void divide_into_Two_2(SLList<T>& retList);

	/*
	* "递增有序的"单链表，去除数值相同的元素，使表中不再有重复的元素。
	*/
	void beingNoSameElement();

	/*
	* 两个递增的单链表合并成一个递减的单链表。
	* 要求：利用原来的结点作为合并后的链表的结点。
	* 方法：两个工作指针分别指向两个表的首结点，比较他们当前所指的两个结点的元素值，
	* （原来升序，生成降序+用头插法）-->取Min，举例模拟，快速确定。
	*/
	void emergetoNewList(SLList<T>& list);

	/*
	* 生成一个新的具有两个递增链表（元素值唯一）的公共元素值的链表, 不破坏原来的链表。
	* 结果保存在generatedList
	*/
	void generateCommonVlaueList(SLList<T>& list, SLList<T>& generatedList);

	/*
	* 生成一个新的具有两个递增链表（元素值唯一）的公共元素值的链表, 利用原来的链表的结点。
	* 结果保存在当前链表。
	*/
	void generateCommonVlaueList(SLList<T>& list);

	/*
	* 是否存在子序列，i.e. mode match.
	* 循环穷举
	*/
	bool modeMatch(SLList<T>& modeList);

	/*
	* 是否(尾部)有环
	* 快慢指针思想
	*/
	bool is_with_a_Loop();

	/*
	* 408真题
	* 获取单链表倒数第K个结点的元素 
	* ret:false for failure，true for having the Kth node from the bottom, retValue is the target value.
	*/
	bool gettheKth_fromtheBottom(T& retVlaue, int k);

	/*
	* 408真题
	* |data|<=n, 且data都是整数。使表中无绝对值相同的元素,保留第一次出现的。
	*/
	void beingNoElement_withSameAbsValue(int n);

	/*
	* 408真题
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
	this->length = length;
	va_list vaList;
	va_start(vaList, length);

	//先生成一个头结点
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
	//	if(p)//访问野指针，空指针会发生异常 access vialation
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
	//如果有成员length，直接把pos与length做比较
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
* 原地排序，带头结点。
* 参照原地逆置的实现，看作有序表和待排表，直接插入排序
*/
template<class T>
inline void SLList<T>::insertSort(bool order) {
	Node<T>* p = head->next;//这个工作指针遍历后表unorderedList
	head->next = nullptr;//前表head,尾部断链结尾
	Node<T>* unorderedList = nullptr;//后表unorderedList

	while (p) {
		unorderedList = p->next;

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
	return nullptr;//无公共结点
}

template<class T>
inline void SLList<T>::emerge(SLList<T>& list) {
	Node<T>* p = head;
	while (p->next) {//get the pointer to the rear node.
		p = p->next;
	}
	p->next = list.getHead()->getNext();//list的头结点的析构由list负责
	length += list.getLength();
}

/*
* 递增输出链表元素，并释放结点，不使用辅助空间的做法。
* 先升序排列，后从首结点遍历输出结点的元素值，同时释放当前结点。
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
* 分解成两个表。原来表留下序号为奇数的结点，返回的表retList放序号为偶数的结点，保存元素相对顺序不变。
* 把偶数序号的结点摘出，追加（尾插）到返回表。
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
	//以上是初始状态的选取
	while (p) {
		//准备下轮，备份
		nextP = p->next;
		nextPre = pre->next;
		if (nextP) {
			nextP = nextP->next;
			nextPre = nextPre->next;
		}
		//摘取
		pre->next = p->next;
		//尾插追加
		p->next = nullptr;
		rear->next = p;
		rear = p;
		--length;
		retList.setLength(retList.getLength() + 1);
		//取用备份
		pre = nextPre;
		p = nextP;
	}
}

/*
* divide {a1,b1,a2,b2,...,an,bn} into {a1,a2,...,an} and {bn,...b2,b1}
* 思路：把偶数序号的结点摘出，前置（头插）到返回表。
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
* "递增有序的"单链表，去除数值相同的元素，使表中不再有重复的元素。
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
			p = p->next;//末尾几个相等的情况
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
	//in case 末尾几个相等的情况
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
* 两个递增的单链表合并成一个递减的单链表。
* 要求：利用原来的结点作为合并后的链表的结点。
* 方法：两个工作指针分别指向两个表的首结点，比较他们当前所指的两个结点的元素值，
* （原来升序，生成降序+用头插法）-->取Min，举例模拟，快速确定。
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
			temp = listP->next;//note: 目的就是listP->next,直接copy它而不是listP，防止后面被改了。
			listP->next = head->next;//防止后面被改了，后面所指此处
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
* 生成一个新的具有两个递增链表（元素值唯一）的公共元素值的链表, 不破坏原来的链表
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
				listP = listP->next;//这次更新可以减少一次冗余的比较
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
* 生成一个新的具有两个递增链表（元素值唯一）的公共元素值的链表, 利用原来的链表的结点。
* 结果保存在当前链表。
*/
template<class T>
inline void SLList<T>::generateCommonVlaueList(SLList<T>& list) {
	Node<T>* p = head->next;
	Node<T>* pre = head;//使被摘取结点的链表的其他结点依然成链，便于释放。
	Node<T>* listP = list.getHead();
	Node<T>* newHeadNode = new Node<T>;//公共结点先连接到这个结点之后
	int insertCnt = 0;
	while (listP) {
		while (p) {
			if (p->data == listP->data) {
				pre->next = p->next;
				Node<T>* temp = p->next;//copy直接目标，避免在后面的被插入过程中被篡改

				p->next = newHeadNode->next;
				newHeadNode->next = p;

				p = temp;//update,不同与上一个问题，此题中有摘取操作
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
* 是否存在子序列，i.e. mode match.
* 循环穷举
*/
template<class T>
inline bool SLList<T>::modeMatch(SLList<T>& modeList) {
	Node<T>* nextP = head->next;
	Node<T>* p = nextP;
	Node<T>* modeListP = modeList.getHead()->getNext();
	//while(nextP){ while(p && modeListP) {...} } ,
	//note:只要一层循环就足够。由于p先于nextP，所以只要nextP不为null, nextP就不会为null。外层的条件冗余了。
	while (p && modeListP) {//相等同步后移，不等“复原”。
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
* 是否(尾部)有环
* 快慢指针思想
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
	else//slow在环里才会追上quick
		return true;
}

/*
* 408真题
* 获取单链表倒数第K个结点的元素
* ret:false for failure，true for having the Kth node from the bottom, retValue is the target value.
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
* 408真题
* |data|<=n, 且data都是整数。使表中无绝对值相同的元素,保留第一次出现的。
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
* 408真题
* {a1,a2,a3,...,an-1,an} --> {a1,an,a2,an-1,a3...}
*/
template<class T>
inline void SLList<T>::rearrange() {
	Node<T>* pFormerLs = head->next;
	Node<T>* pLaterLs = nullptr;//前表的最后结点需要断链。
	Node<T>* pLaterLsPre = head;
	int halfNum = (length + 1) / 2;//令前表长，后表短，优点：每个后表结点都会被插入到前表，操作统一，不需要做额外的判断。
	halfNum;//pLaterLsPre从head移动到后表的头结点所需跳数		
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
		pFormerLs = pFormerLs->next->next;//前表只会更长，必定不为nullptr
	}
}


