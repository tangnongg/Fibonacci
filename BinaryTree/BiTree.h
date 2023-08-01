#pragma once

#include "SqBiTree.h"
//#include <Queue>//队列在树的层序遍历中的应用
//#include "Queue.h"//vs is shit!!
#include <vector>
#include <iostream>
#include <stack>


template<class T> class BiNode;
template<class T>
class BiNode {
	friend class BiTree<T>;
protected:
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

	/*
	* 用后序析构
	*/
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
	* 以层序序列的顺序把元素输出
	*/
	void traverseLevelOrder(BiNode<T>* parent);
	void traverseLevelOrder() {
		std::cout << "层序遍历序列：";
		traverseLevelOrder(root);
		std::cout << std::endl;
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

	/*
	* 非递归后序遍历
	*/
	void traversePostOrder_NonRecursive(BiNode<T>* parent);
	void traversePostOrder_NonRecursive() {
		std::cout << "非递归后序遍历序列：";	
		traversePostOrder_NonRecursive(root);
		std::cout << std::endl;
	}

	/*
	* 改编非递归后序遍历，获取祖先结点到子孙结点的路径
	*/
	void getPath_fromAncestortoDescendant(BiNode<T>* ancestor, T descendant, std::vector<T>& retVec);
	void getPath_fromAncestortoDescendant(T descendant, std::vector<T>& retVec) {
		getPath_fromAncestortoDescendant(root, descendant, retVec);
	}

	/*
	* 求二叉树的高度，递归方式
	*/
	int getHigh(BiNode<T>* parent);
	int getHigh() {
		return getHigh(root);
	}

	/*
	* 改编非递归后序遍历，求二叉树的高度
	*/
	int getHigh_PostOrder_NonRecursive(BiNode<T>* parent);
	int getHigh_PostOrder_NonRecursive() {
		return getHigh_PostOrder_NonRecursive(root);
	}
};








/*类模板的成员函数的【全 - 部参数】特例化1 */
template<>
inline void BiTree<int>::createBiTree_from_SqBiTree(SqBiTree<int>& sqBiTree, int i, BiNode<int>*& parent) {//note:不能把成员变量root作为成员函数参数默认值
	if (parent != nullptr)//初始树必须为空树，避免内存泄露
		return;
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
	if (parent != nullptr)//初始树必须为空树，避免内存泄露
		return;
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
* 以层序序列的顺序把元素输出
*/
template<class T>
inline void BiTree<T>::traverseLevelOrder(BiNode<T>* parent) {
	Queue<BiNode<T>*> que(100);
	que.push(parent);
	BiNode<T>* p = nullptr;
	while (!que.empty()) {
		p = que.front();
		std::cout << p->data << ",";
		que.pop();
		if (p->lchild)
			que.push(p->lchild);
		if (p->rchild)
			que.push(p->rchild);
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

/*
* 非递归后序遍历
*/
template<class T>
inline void BiTree<T>::traversePostOrder_NonRecursive(BiNode<T>* parent) {
	std::stack<BiNode<T>*> stk;
	BiNode<T>* recent = nullptr;
	BiNode<T>* p = parent;
	while (p || !stk.empty()) {
		if (p) {
			stk.push(p);
			p = p->lchild;
		}
		else {
			p = stk.top();
			if (p->rchild && recent != p->rchild) {
				p = p->rchild;
			}
			else {
				stk.pop();
				std::cout << p->data << ",";
				recent = p;
				p = nullptr;
			}
		}
	}
}

/*
* 改编非递归后序遍历，获取祖先结点到子孙结点的路径
*/
template<class T>
inline void BiTree<T>::getPath_fromAncestortoDescendant(BiNode<T>* ancestor, T descendant, std::vector<T>& retVec) {
	std::stack<BiNode<T>*> stk;
	BiNode<T>* recent = nullptr;
	BiNode<T>* p = ancestor;
	while (p || !stk.empty()) {
		if (p) {
			stk.push(p);
			p = p->lchild;
		}
		else {
			p = stk.top();
			if (p->rchild && recent != p->rchild) {
				p = p->rchild;
			}
			else {
				stk.pop();
				/**********************************/
				if (p->data == descendant) {
					retVec.push_back(p->data);
					while (!stk.empty())
					{
						retVec.push_back(stk.top()->data);
						stk.pop();
					}
					break;
				}
				/***********************************/
				recent = p;
				p = nullptr;
			}
		}
	}
}

/*
* 求二叉树的高度，递归方式
*/
template<class T>
inline int BiTree<T>::getHigh(BiNode<T>* parent) {
	if (parent) {
		int lHigh = getHigh(parent->lchild);
		int rHigh = getHigh(parent->rchild);
		return lHigh > rHigh ? lHigh + 1 : rHigh + 1;
	}
	else
		return 0;
}

/*
* 改编非递归后序遍历，求二叉树的高度
*/
template<class T>
inline int BiTree<T>::getHigh_PostOrder_NonRecursive(BiNode<T>* parent) {
	std::stack<BiNode<T>*> stk;
	BiNode<T>* recent = nullptr;
	BiNode<T>* p = parent;
	int stkDeepth = 0;
	int maxStkDeepth = 0;
	while (p || !stk.empty()) {
		if (p) {
			stk.push(p);
			++stkDeepth;
			maxStkDeepth = stkDeepth > maxStkDeepth ? stkDeepth : maxStkDeepth;
			p = p->lchild;
		}
		else {
			p = stk.top();
			if (p->rchild && recent != p->rchild) {
				p = p->rchild;
			}
			else {
				stk.pop();
				--stkDeepth;
				std::cout << p->data << ",";
				recent = p;
				p = nullptr;
			}
		}
	}
	return maxStkDeepth;
}






