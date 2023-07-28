
/*
* ˳��ջ��that Stack means by default������ջ������ջ
*/

/***************************************************
*		Stack ˳��ջ(����ʵ��)
*		��std::stack's interface.
******************************************************/
template<class T> 
class Stack {
private:
	T* dataArr;
	int topIdx;//topIdx's initial value is -1, which means topIdx refers to the topIdx element(except in the empty state), not the next of the topIdx element.
	int size;
	//int count;//��ά��

public:
	Stack():
		dataArr(nullptr), topIdx(-1), size(0)
	{}

	Stack(int size) :
		dataArr(new T[size]), topIdx(-1), size(size)
	{}

	~Stack() {
		delete [] dataArr;
	}

	const int& getSize() {
		return size;
	}

	bool empty();

	const T& top();

	void push(const T& elem);

	void pop();
};

template<class T>
inline bool Stack<T>::empty() {
	if (topIdx == -1)
		return true;
	else
		return false;
}

template<class T>
inline const T& Stack<T>::top() {//��ջ���ʵķ��ش���---�쳣
	if (!empty())
		return(dataArr[topIdx]);
	else
		throw "acssing empty stack.";
}

template<class T>
inline void Stack<T>::push(const T& elem) {
	if (topIdx + 1 > size - 1)//��ջ�������������쳣������̬����
		throw "push an element into a full stack.";
	++topIdx;
	dataArr[topIdx] = elem;
}

template<class T>
inline void Stack<T>::pop() {
	if (topIdx == -1)//��ջ�пգ��������쳣
		throw "pop an element from a empty stack.";
	dataArr[topIdx] = T();//������Բ鿴
	--topIdx;
}


/*************************
* todo: SharedStack
**************************/


/*************************
* todo: LinkedStack
**************************/