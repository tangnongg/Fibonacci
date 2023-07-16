
template<class T>
class Node {
private:
	T data;
	Node<T>* lchild;
	Node<T>* rchild;

public:
	Node() :
		data(), lchild(nullptr), lchild(nullptr)
	{}

	Node(const T& data, Node<T>* lchild, Node<T>* rchild):
		data(data),lchild(lchild),rchild(rchild)
	{}
};

template<class BiTree
{
private:
	Node<T>* root;
	int cnt;
	int high;

public:
	BiTree() :
		root(nullptr), cnt(0), high(0)
	{}

	~BiTree()
	{
	
	}

};
