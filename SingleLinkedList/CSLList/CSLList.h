#include <iostream>
#include <cstdarg>
#include <vector>

/********************************************
*			���Ķ���
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
* ��ͷ��㣬����βָ���ѭ��������by default)
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
	* ����һ�������ӵ��ñ�֮��
	*/
	void emerge(CSLList<T>& list);

	/*
	* ����ɾ��Ԫ��ֵ��С�Ľ��
	* method 1:ÿ������С�������ɾ����(ÿ�β��ƻ�ԭ�������˳��
	* method 2�����������������ɾ��
	*/
	void deleteMinRepeatly(std::vector<T>& vec) {
		while (head->next != head) {
			vec.push_back(deleteMin());
		}
	}

	/*
	* ����С�����(��Ϊ����ֵ����ɾ��
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
		Node<T>* newNode = new Node<T>(va_arg(vaList, T), rear->next);//β����next������ֱ����nullptr��
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
* ����һ�������ӵ��ñ�֮��
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
