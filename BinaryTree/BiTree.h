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

	void traversePostOrder_for_Delete(BiNode<T>* parent);

	/*
	 * 只能用后序遍历去释放树中的结点，不同于只遍历不释放，释放之后结点的指针域也访问不了。
	*/
	~BiTree()
	{
		traversePostOrder_for_Delete(root);
	}

	const int& getCount() {
		return count;
	}

	/*
	* 用顺序存储二叉树初始化一个二叉链表存储二叉树
	*/
	void createBiTree_from_SqBiTree(SqBiTree<T>& sqBiTree, int i, BiNode<T>*& parent);//定义两个特例化
	void createBiTree_from_SqBiTree(SqBiTree<T>& sqBiTree);//为了封装上面的同名函数，因为不能把成员变量root作为成员函数参数默认值

	/*
	* 以先序序列的顺序把元素输出
	*/
	void traversePreOrder(BiNode<T>* parent);
	void traversePreOrder() {
		std::cout << "先序遍历序列：";
		traversePreOrder(root);
		std::cout << std::endl;
	}

	/*
	* 以先序序列的顺序把元素放到vector中
	*/
	void printAlltoVecPreOrder(BiNode<T>* parent, std::vector<T>& vec);
	void printAlltoVecPreOrder(std::vector<T>& vec) {
		printAlltoVecPreOrder(root, vec);
	}

	/*
	* 以后序序列的顺序把元素输出
	*/
	void traversePostOrder(BiNode<T>* parent);
	void traversePostOrder() {
		std::cout << "后序遍历序列：";
		traversePostOrder(root);
		std::cout << std::endl;
	}

	//todo:层序遍历，图形化输出

	//todo:非递归后序遍历，和相关算法（祖先结点到孩子结点的路径，树高）
};




/*类模板的成员函数的【全 - 部参数】特例化1 */
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

/*类模板的成员函数的【全 - 部参数】特例化2*/
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
/*
* 以先序序列的顺序把元素输出
*/
template<class T>
inline void BiTree<T>::traversePreOrder(BiNode<T>* parent) {
	if (parent) {
		std::cout << parent->data;
		traversePreOrder(parent->lchild);
		traversePreOrder(parent->rchild);
	}
}

/*
* 用后序析构
*/
template<class T>
inline void BiTree<T>::traversePostOrder_for_Delete(BiNode<T>* parent) {
	if (parent) {
		traversePostOrder_for_Delete(parent->lchild);
		traversePostOrder_for_Delete(parent->rchild);
		delete parent;
	}
}

/*
* 以前序序列的顺序把元素放到vector中
*/
template<class T>
inline void BiTree<T>::printAlltoVecPreOrder(BiNode<T>* parent, std::vector<T>& vec) {
	if (parent) {
		vec.push_back(parent->data);
		printAlltoVecPreOrder(parent->lchild, vec);
		printAlltoVecPreOrder(parent->rchild, vec);
	}
}

/*
* 以后序序列的顺序把元素输出
*/
template<class T>
inline void BiTree<T>::traversePostOrder(BiNode<T>* parent) {
	if (parent) {
		traversePostOrder(parent->lchild);
		traversePostOrder(parent->rchild);
		std::cout << parent->data;
	}
}


