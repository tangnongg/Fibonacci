#include <cstdarg>
#include <iostream>
#include <vector>

/****************************
*       Node
*    ����һ��freq��int����
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
*       DLList(��ͷ���)
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
	* ÿ����һ�δ˲���������Ԫ��ֵx�Ľ�㣨�ٶ�����Ԫ��ֵΨһ����freq��һ��
	* ��ʹ���н�㰴freqֵ�ݼ�����������ʹ��Ľ�����ھ�����ͬfreqֵ�Ľ���ǰ�棬
	*���ٶ���ʼ��������ѭ��Ҫ�󣬳�ʼ״̬����Ϊ����freqȫ0����ôֻ��Ҫȷ���ոձ����ʵĽ��Ĳ���λ�ã���
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
* ÿ����һ�δ˲���������Ԫ��ֵx�Ľ�㣨�ٶ�����Ԫ��ֵΨһ����freq��һ��
* ��ʹ���н�㰴freqֵ�ݼ�����������ʹ��Ľ�����ھ�����ͬfreqֵ�Ľ���ǰ�棬
*���ٶ���ʼ��������ѭ��Ҫ�󣬳�ʼ״̬����Ϊ����freqȫ0����ôֻ��Ҫȷ���ոձ����ʵĽ��Ĳ���λ�ã���
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
	if (p == nullptr)//�޾���xԪ��ֵ�Ľ��
		exit(-1);
	else {//pָ�򱻷��ʽ�㣬����Ѱ�Ҳ���λ��
		++p->freq;
		Node<T>* insertPos = head->next;
		while (insertPos != p) {
			if (insertPos->freq <= p->freq) {//<=
											 //ժ����������λ��
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
		}//ֻ������ǰ�壬�����ﷵ�ر�ʾ��������ԭ��λ�ã�����ժ�������롣
		return p;
	}
}
