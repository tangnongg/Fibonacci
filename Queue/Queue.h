
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
	bool empty() {
		if (frontIdx == rearIdx)
			return true;
		else
			return false;
	}

	/*
	* ѭ�����п��㣬����
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
		if (full())//����������������쳣������̬����
			throw "push an element into a full queue.";
		dataArr[rearIdx] = elem;
		rearIdx = (rearIdx + 1) % size;	
	}

	/*
	* Removes the next element in the queue, effectively reducing its size by one.
	*/
	void pop() {
		if (empty())//����������������쳣������̬����
			throw "pop an element from a empty queue.";
		dataArr[frontIdx] = T();//������Բ鿴
		frontIdx = (frontIdx + 1) % size;
	}

	/*
	* ���ʶ�ͷ
	*/
	const T& front() {
		if (!empty())
			return dataArr[frontIdx];
		else
			throw "empty queue.";
	}

	/*
	* ���ʶ�β
	*/
	const T& back() {
		if (!empty())
			return dataArr[(rearIdx - 1 + size) % size];
		else
			throw "empty queue.";
	}
};