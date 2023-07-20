#include "SqBiTree.h"
#include <vector>
#include <iostream>

template<class T> class BiNode;
template<class T>
class BiNode {
	friend class BiTree<T>;
private:
	T data;
	BiNode<T>* lchild;
	BiNode<T>* rchild;

public:
	BiNode() :
		data(), lchild(nullptr), lchild(nullptr)
	{}

	BiNode(const T& data, BiNode<T>* lchild, BiNode<T>* rchild):
		data(data),lchild(lchild),rchild(rchild)
	{}
};

template<class T>
class BiTree
{
private:
	BiNode<T>* root;
	int count;

public:
	BiTree() :
		root(nullptr), count(0)
	{}

	~BiTree()
	{
	
	}

	const int& getCount() {
		return count;
	}

	void createBiTree_from_SqBiTree(SqBiTree<T>& sqBiTree, int i, BiNode<T>*& parent);//定义两个特例化

	void createBiTree_from_SqBiTree(SqBiTree<T>& sqBiTree);//为了封装上面的同名函数，因为不能把成员变量root作为成员函数参数默认值

	//todo:层序遍历，图形化
	void traversePreOrder(BiNode<T>* parent) {
		if (parent) {
			std::cout << parent->data << std::endl;
			traversePreOrder(parent->lchild);
			traversePreOrder(parent->rchild);
		}
	}

	void traversePreOrder() {
		traversePreOrder(root);
	}

	void printAlltoVecPreOrder(BiNode<T>* parent, std::vector<T>& vec) {
		if (parent) {
			vec.push_back(parent->data);
			printAlltoVecPreOrder(parent->lchild, vec);
			printAlltoVecPreOrder(parent->rchild, vec);
		}
	}

	void printAlltoVecPreOrder(std::vector<T>& vec) {
		printAlltoVecPreOrder(root, vec);
	}
};

//类模板的成员函数的【全-部参数】特例化1
template<>
inline void BiTree<int>::createBiTree_from_SqBiTree(SqBiTree<int>& sqBiTree, int i, BiNode<int>*& parent) {//note:不能把成员变量root作为成员函数参数默认值
	if (sqBiTree.dataArr[i] != -1 && i <= sqBiTree.count)
		parent = new BiNode<int>(sqBiTree.dataArr[i], nullptr, nullptr);
	else
		return;
	createBiTree_from_SqBiTree(sqBiTree, 2 * i, parent->lchild);
	createBiTree_from_SqBiTree(sqBiTree, 2 * i + 1, parent->rchild);
}
template<>
inline void BiTree<int>::createBiTree_from_SqBiTree(SqBiTree<int>& sqBiTree) {//封装一下
	createBiTree_from_SqBiTree(sqBiTree, 1, root);
	count = sqBiTree.count;
}

//类模板的成员函数的【全-部参数】特例化2
template<>
inline void BiTree<char>::createBiTree_from_SqBiTree(SqBiTree<char>& sqBiTree, int i, BiNode<char>*& parent) {
	if (sqBiTree.dataArr[i] != '*' && i <= count)
		parent = new BiNode<char>(sqBiTree.dataArr[i], nullptr, nullptr);
	createBiTree_from_SqBiTree(sqBiTree, 2 * i, parent->lchild);
	createBiTree_from_SqBiTree(sqBiTree, 2 * i + 1, parent->rchild);
}
template<>
inline void BiTree<char>::createBiTree_from_SqBiTree(SqBiTree<char>& sqBiTree) {//封装一下
	createBiTree_from_SqBiTree(sqBiTree, 1, root);
	count = sqBiTree.count;
}
