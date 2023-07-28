
/*
* 顺序栈（that Stack means by default），链栈，共享栈
*/

/***************************************************
*		Stack 顺序栈(数组实现)
*		仿std::stack's interface.
******************************************************/
template<class T> 
class Stack {
private:
	T* dataArr;
	int topIdx;//topIdx's initial value is -1, which means topIdx refers to the topIdx element(except in the empty state), not the next of the topIdx element.
	int size;
	//int count;//不维护

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
inline const T& Stack<T>::top() {//空栈访问的返回处理---异常
	if (!empty())
		return(dataArr[topIdx]);
	else
		throw "acssing empty stack.";
}

template<class T>
inline void Stack<T>::push(const T& elem) {
	if (topIdx + 1 > size - 1)//入栈判满，满则抛异常，不动态增长
		throw "push an element into a full stack.";
	++topIdx;
	dataArr[topIdx] = elem;
}

template<class T>
inline void Stack<T>::pop() {
	if (topIdx == -1)//出栈判空，空则抛异常
		throw "pop an element from a empty stack.";
	dataArr[topIdx] = T();//方便调试查看
	--topIdx;
}


/*************************
* todo: SharedStack
**************************/


/*************************
* todo: LinkedStack
**************************/