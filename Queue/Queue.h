
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
	bool empty() {
		if (frontIdx == rearIdx)
			return true;
		else
			return false;
	}

	/*
	* 循环队列考点，判满
	*/
	bool full() {
		if ((rearIdx + 1) % size == frontIdx)
			return true;
		else
			return false;
	}

	/*
	* Inserts a new element at the end of the queue, after its current last element.
	*/	
	void push(const T& elem) {
		if (full())//入队判满，满则抛异常，不动态增长
			throw "push an element into a full queue.";
		dataArr[rearIdx] = elem;
		rearIdx = (rearIdx + 1) % size;	
	}

	/*
	* Removes the next element in the queue, effectively reducing its size by one.
	*/
	void pop() {
		if (empty())//入队判满，满则抛异常，不动态增长
			throw "pop an element from a empty queue.";
		dataArr[frontIdx] = T();//方便调试查看
		frontIdx = (frontIdx + 1) % size;
	}

	/*
	* 访问队头
	*/
	const T& front() {
		if (!empty())
			return dataArr[frontIdx];
		else
			throw "empty queue.";
	}

	/*
	* 访问队尾
	*/
	const T& back() {
		if (!empty())
			return dataArr[(rearIdx - 1 + size) % size];
		else
			throw "empty queue.";
	}
};