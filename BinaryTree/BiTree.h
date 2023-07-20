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

	void createBiTree_from_SqBiTree(SqBiTree<T>& sqBiTree, int i, BiNode<T>*& parent);//��������������

	void createBiTree_from_SqBiTree(SqBiTree<T>& sqBiTree);//Ϊ�˷�װ�����ͬ����������Ϊ���ܰѳ�Ա����root��Ϊ��Ա��������Ĭ��ֵ

	//todo:���������ͼ�λ�
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

//��ģ��ĳ�Ա�����ġ�ȫ-��������������1
template<>
inline void BiTree<int>::createBiTree_from_SqBiTree(SqBiTree<int>& sqBiTree, int i, BiNode<int>*& parent) {//note:���ܰѳ�Ա����root��Ϊ��Ա��������Ĭ��ֵ
	if (sqBiTree.dataArr[i] != -1 && i <= sqBiTree.count)
		parent = new BiNode<int>(sqBiTree.dataArr[i], nullptr, nullptr);
	else
		return;
	createBiTree_from_SqBiTree(sqBiTree, 2 * i, parent->lchild);
	createBiTree_from_SqBiTree(sqBiTree, 2 * i + 1, parent->rchild);
}
template<>
inline void BiTree<int>::createBiTree_from_SqBiTree(SqBiTree<int>& sqBiTree) {//��װһ��
	createBiTree_from_SqBiTree(sqBiTree, 1, root);
	count = sqBiTree.count;
}

//��ģ��ĳ�Ա�����ġ�ȫ-��������������2
template<>
inline void BiTree<char>::createBiTree_from_SqBiTree(SqBiTree<char>& sqBiTree, int i, BiNode<char>*& parent) {
	if (sqBiTree.dataArr[i] != '*' && i <= count)
		parent = new BiNode<char>(sqBiTree.dataArr[i], nullptr, nullptr);
	createBiTree_from_SqBiTree(sqBiTree, 2 * i, parent->lchild);
	createBiTree_from_SqBiTree(sqBiTree, 2 * i + 1, parent->rchild);
}
template<>
inline void BiTree<char>::createBiTree_from_SqBiTree(SqBiTree<char>& sqBiTree) {//��װһ��
	createBiTree_from_SqBiTree(sqBiTree, 1, root);
	count = sqBiTree.count;
}
