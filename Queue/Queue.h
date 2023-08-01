#pragma once
/*****************************************************************
* 循环队列（which Queue refers to by default), 链式队列，双端队列 
****************************************************************/


/*******************************************************
*		Queue 循环队列(数组实现）
*		仿std::queue's interface
*******************************************************/
template<class T>
class Queue {
private:
	T* dataArr;
	int size;
	int frontIdx;//非初始状态下，frontIdx指向队头，rearIdx指向队尾的下一个位置。
	int rearIdx;//initial state(empty queue):frontIdx=0, rearIdx=0.
	//int count;//不维护。如果增设count成员变量表示当前队内元素个数，方便判空、满。就不需要采用“牺牲一个单元法”区分判空、满条件

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
	* 循环队列考点，判空
	*/
	bool empty();

	/*
	* 循环队列考点，判满
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
	* 访问队头
	*/
	const T& front();

	/*
	* 访问队尾
	*/
	const T& back();
};


/*****************************************
* 408真题
* requirements:
* 1.初始队列为空;
* 2.入队时，允许增加队列占用空间；
* 3.出队后，出队元素所占用的空间可重复利用；
* 4.入队、出队操作的时间复杂度始终为O(1)。
******************************************/

/*******************************************
*			循环单链队列（仿循环队列）
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
	Node<T>* frontPtr;//仿照循环队列，牺牲一个单元以区分队空、队满.
	Node<T>* rearPtr;//frontPtr指向队头，near指向队尾的下一个位置。

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
	if (full()) {//队满，增加结点：在rearPtr后增加结点作为新的牺牲结点，原牺牲结点作为本次入队元素的存放结点。
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
* 循环队列考点，判空
*/
template<class T>
inline bool Queue<T>::empty() {
	if (frontIdx == rearIdx)
		return true;
	else
		return false;
}

/*
* 循环队列考点，判满
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
	if (full())//入队判满，满则抛异常，不动态增长
		throw "push an element into a full queue.";
	dataArr[rearIdx] = elem;
	rearIdx = (rearIdx + 1) % size;
}

/*
* Removes the next element in the queue, effectively reducing its size by one.
*/
template<class T>
inline void Queue<T>::pop() {
	if (empty())//入队判满，满则抛异常，不动态增长
		throw "pop an element from a empty queue.";
	dataArr[frontIdx] = T();//方便调试查看
	frontIdx = (frontIdx + 1) % size;
}

/*
* 访问队头
*/
template<class T>
inline const T& Queue<T>::front() {
	if (!empty())
		return dataArr[frontIdx];
	else
		throw "front():empty queue.";
}

/*
* 访问队尾
*/
template<class T>
inline const T& Queue<T>::back() {
	if (!empty())
		return dataArr[(rearIdx - 1 + size) % size];
	else
		throw "back():empty queue.";
}
