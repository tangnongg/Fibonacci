#pragma once
/*****************************************************************
* ѭ�����У�which Queue refers to by default), ��ʽ���У�˫�˶��� 
****************************************************************/


/*******************************************************
*		Queue ѭ������(����ʵ�֣�
*		��std::queue's interface
*******************************************************/
template<class T>
class Queue {
private:
	T* dataArr;
	int size;
	int frontIdx;//�ǳ�ʼ״̬�£�frontIdxָ���ͷ��rearIdxָ���β����һ��λ�á�
	int rearIdx;//initial state(empty queue):frontIdx=0, rearIdx=0.
	//int count;//��ά�����������count��Ա������ʾ��ǰ����Ԫ�ظ����������пա������Ͳ���Ҫ���á�����һ����Ԫ���������пա�������

public:
	Queue():
		dataArr(nullptr), size(0), frontIdx(0), rearIdx(0)
	{}

	Queue(int size) :
		dataArr(new T[size]), size(size), frontIdx(0), rearIdx(0)
	{}

	~Queue() {
		delete dataArr;
	}

	const int& getSize() {
		return size;
	}

	/*
	* ѭ�����п��㣬�п�
	*/
	bool empty();

	/*
	* ѭ�����п��㣬����
	*/
	bool full();

	/*
	* Inserts a new element at the end of the queue, after its current last element.
	*/	
	void push(const T& elem);

	/*
	* Removes the next element in the queue, effectively reducing its size by one.
	*/
	void pop();

	/*
	* ���ʶ�ͷ
	*/
	const T& front();

	/*
	* ���ʶ�β
	*/
	const T& back();
};


/*****************************************
* 408����
* requirements:
* 1.��ʼ����Ϊ��;
* 2.���ʱ���������Ӷ���ռ�ÿռ䣻
* 3.���Ӻ󣬳���Ԫ����ռ�õĿռ���ظ����ã�
* 4.��ӡ����Ӳ�����ʱ�临�Ӷ�ʼ��ΪO(1)��
******************************************/

/*******************************************
*			ѭ���������У���ѭ�����У�
********************************************/
template<class T>class CSLQueue;
template<class T>
class Node {
	friend class CSLQueue<T>;
private:
	T data;
	Node<T>* next;
};

template<class T>
class CSLQueue {
private:
	Node<T>* frontPtr;//����ѭ�����У�����һ����Ԫ�����ֶӿա�����.
	Node<T>* rearPtr;//frontPtrָ���ͷ��nearָ���β����һ��λ�á�

public:
	CSLQueue();

	~CSLQueue();

	bool empty();

	bool full();

	void push(const T& elem);

	void pop();

	const T& front();

	const T& back();
};

template<class T>
inline CSLQueue<T>::CSLQueue() {
	frontPtr = new Node<T>;
	frontPtr->next = frontPtr;
	rearPtr = frontPtr;
}

template<class T>
inline CSLQueue<T>::~CSLQueue() {
	Node<T>* stopPos = frontPtr;
	Node<T>* p = frontPtr;
	Node<T>* nextP = nullptr;
	while (p != stopPos) {
		nextP = frontPtr->next;
		if (p)
			delete p;
		p = nextP;
	}
}

template<class T>
inline bool CSLQueue<T>::empty() {
	if (rearPtr == frontPtr)
		return true;
	else
		return false;
}

template<class T>
inline bool CSLQueue<T>::full() {
	if (rearPtr->next == frontPtr)
		return true;
	else
		return false;
}

template<class T>
inline void CSLQueue<T>::push(const T& elem) {
	if (full()) {//���������ӽ�㣺��rearPtr�����ӽ����Ϊ�µ�������㣬ԭ���������Ϊ�������Ԫ�صĴ�Ž�㡣
		Node<T>* newNode = new Node<T>;
		newNode->next = frontPtr;
		rearPtr->next = newNode;
	}
	rearPtr->data = elem;
	rearPtr = rearPtr->next;
}

template<class T>
inline void CSLQueue<T>::pop() {
	if (empty())
		throw "pop an element from a empty queue.";
	else {
		frontPtr->data = T();//for the sake of debugging
		frontPtr = frontPtr->next;
	}
}

template<class T>
inline const T& CSLQueue<T>::front() {
	if (empty())
		throw "front():acessing an empty queue.";
	return frontPtr->data;
}

template<class T>
inline const T& CSLQueue<T>::back() {
	if (empty())
		throw "back():acessing an empty queue.";
	Node<T>* p = rearPtr->next;
	while (p->next != rearPtr)
		p = p->next;
	return p->data;
}

/*
* ѭ�����п��㣬�п�
*/
template<class T>
inline bool Queue<T>::empty() {
	if (frontIdx == rearIdx)
		return true;
	else
		return false;
}

/*
* ѭ�����п��㣬����
*/
template<class T>
inline bool Queue<T>::full() {
	if ((rearIdx + 1) % size == frontIdx)
		return true;
	else
		return false;
}

/*
* Inserts a new element at the end of the queue, after its current last element.
*/
template<class T>
inline void Queue<T>::push(const T& elem) {
	if (full())//����������������쳣������̬����
		throw "push an element into a full queue.";
	dataArr[rearIdx] = elem;
	rearIdx = (rearIdx + 1) % size;
}

/*
* Removes the next element in the queue, effectively reducing its size by one.
*/
template<class T>
inline void Queue<T>::pop() {
	if (empty())//����������������쳣������̬����
		throw "pop an element from a empty queue.";
	dataArr[frontIdx] = T();//������Բ鿴
	frontIdx = (frontIdx + 1) % size;
}

/*
* ���ʶ�ͷ
*/
template<class T>
inline const T& Queue<T>::front() {
	if (!empty())
		return dataArr[frontIdx];
	else
		throw "front():empty queue.";
}

/*
* ���ʶ�β
*/
template<class T>
inline const T& Queue<T>::back() {
	if (!empty())
		return dataArr[(rearIdx - 1 + size) % size];
	else
		throw "back():empty queue.";
}
