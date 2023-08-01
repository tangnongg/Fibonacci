#pragma once
#include "SqBiTree.h"

/**********************************
*    ThreadBiNode线索二叉树
**********************************/
template<class T> class ThreadBiTree;
template <class T>
class ThreadBiNode {
	friend class ThreadBiTree<T>;
private:
	T data;
	ThreadBiNode<T>* lchild;
	ThreadBiNode<T>* rchild;
	bool ltag;//true means lchild refers to the successor of this node.
	bool rtag;////true means lchild refers to the predecessor of this node.

public:
	ThreadBiNode() :
		data(), lchild(nullptr), lchild(nullptr), ltag(true), rtag(true)
	{}

	ThreadBiNode(const T& data, ThreadBiNode<T>* lchild, ThreadBiNode<T>* rchild, const bool& ltag, const bool& rtag) :
		data(data), lchild(lchild), rchild(rchild), ltag(ltag), rtag(rtag)
	{}

};

template<class T>
class ThreadBiTree {
private:
	ThreadBiNode<T>* root;
	int count;

public:
	ThreadBiTree() :
		root(nullptr), count(0)
	{}

	void createBiTree_from_SqBiTree(SqBiTree<T>& sqBiTree, int i, ThreadBiNode<T>*& parent);//定义1个特例化
	void createBiTree_from_SqBiTree(SqBiTree<T>& sqBiTree);//为了封装上面的同名函数，因为不能把成员变量root作为成员函数参数默认值

	/*
	 * 用中序线索遍历去释放树中的结点
	*/
	~ThreadBiTree();

	/*
	 *中序遍历 infix order
	*/
	void traverseInOrder(ThreadBiNode<T>*& parent);
	void traverseInOrder();

	/*
	 *中序线索化(recursive)
	 * input:p, the working pointer to the current node; pre, the pointer to the previous node just visited.
	*/
	void thread(ThreadBiNode<T>*& p, ThreadBiNode<T>*& pre);
	void thread() {
		ThreadBiNode<T>* pre = nullptr;
		thread(root, pre);// err: cannot convert argument 2 from 'nullptr' to 'ThreadBiNode<T> *&
		//do note:中序最后一个结点的后继没有处理（只设置前一个结点的中序后继线索）;---->>结点初始化时默认为true.
	}
	/*
	 *根据中序后继线索遍历二叉树，得到中序遍历序列
	*/
	void traverse_by_InfixThread();
};





/*类模板的成员函数的【全 - 部参数】特例化1 */
template<>
inline void ThreadBiTree<int>::createBiTree_from_SqBiTree(SqBiTree<int>& sqBiTree, int i, ThreadBiNode<int>*& parent) {//note:不能把成员变量root作为成员函数参数默认值
	if (parent != nullptr)//初始树必须为空树，避免内存泄露
		return;
	if (sqBiTree.dataArr[i] != -1 && i <= sqBiTree.count)
		parent = new ThreadBiNode<int>(sqBiTree.dataArr[i], nullptr, nullptr, false, false);
	else
		return;
	createBiTree_from_SqBiTree(sqBiTree, 2 * i, (parent->lchild));
	createBiTree_from_SqBiTree(sqBiTree, 2 * i + 1, (parent->rchild));
}
template<>
inline void ThreadBiTree<int>::createBiTree_from_SqBiTree(SqBiTree<int>& sqBiTree) {//封装一下
	createBiTree_from_SqBiTree(sqBiTree, 1, root);
	count = sqBiTree.count;
	std::cout << "before thread():";//方便调试查看
	traverseInOrder();
	thread();//创建后必须线索化，统一析构方法，普通二叉树的析构!=线索二叉树的析构
}

/*
* 用中序线索遍历去释放树中的结点
*/
template<class T>
inline ThreadBiTree<T>::~ThreadBiTree() {
	ThreadBiNode<T>* p = root;
	while (p->lchild)
		p = p->lchild;

	ThreadBiNode<T>* temp = nullptr;
	while (p) {
		temp = p;
		if (p->rtag == true)
			p = p->rchild;
		else {
			p = p->rchild;
			while (p && p->ltag == false)
				p = p->lchild;
		}
		if (temp)
			delete temp;
	}
}



/*
*中序遍历 infix order
*/
template<class T>
inline void ThreadBiTree<T>::traverseInOrder(ThreadBiNode<T>*& parent) {
	if (parent) {
		traverseInOrder(parent->lchild);
		std::cout << parent->data << ",";
		traverseInOrder(parent->rchild);
	}
}

template<class T>
inline void ThreadBiTree<T>::traverseInOrder() {
	std::cout << "中序序列：";
	traverseInOrder(root);
	std::cout << std::endl;
}

/*
*中序线索化(recursive)
* input:p, the working pointer to the current node; pre, the pointer to the previous node just visited.
*/
template<class T>
inline void ThreadBiTree<T>::thread(ThreadBiNode<T>*& p, ThreadBiNode<T>*& pre) {
	if (p) {
		thread(p->lchild, pre);

		if (p->lchild == nullptr) {//设置当前结点的中序前驱线索
			p->ltag = true;
			p->lchild = pre;
		}
		if (pre != nullptr && pre->rchild == nullptr) {//设置前一个结点的中序后继线索
			pre->rtag = true;
			pre->rchild = p;
		}
		pre = p;//更新pre

		thread(p->rchild, pre);
	}
}

/*
*根据中序后继线索遍历二叉树，得到中序遍历序列
*/
template<class T>
inline void ThreadBiTree<T>::traverse_by_InfixThread() {
	//get中序遍历的第一个node
	ThreadBiNode<T>* p = root;
	while (p->lchild)
		p = p->lchild;
	//从这个p node遍历
	while (p) {
		std::cout << p->data << ",";	
		if (p->rtag == true)		
			p = p->rchild;
		else  {//后继在右子树中,即get右子树中序遍历的第一个node
			p = p->rchild;
			while (p && p->ltag==false)//孩子域已经线索化，要求不是线索(&& p->lchild) 
				p = p->lchild;
		}
		
	}
	std::cout << std::endl;
}
