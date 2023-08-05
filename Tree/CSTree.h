#pragma once

#include "SqBiTree.h"
#include <vector>
#include <iostream>
#include <queue>

/*******************************************
*	树结点（孩子兄弟表示法，i.e.二叉树表示法）
********************************************/
template<class T> class CSTree;
template<class T>
class CSTreeNode {
	friend class CSTree<T>;
private:
	T data = T();
	CSTreeNode<T>* firstChild = nullptr;
	CSTreeNode<T>* nextSibling = nullptr;
	//compiler provide a default constructor with zero args.
};

/*******************************************
*	树（孩子兄弟表示法，i.e.二叉树表示法）
*   构造对应二叉树---->>即构造树
********************************************/
template<class T>
class CSTree
{
private:
	CSTreeNode<T>* root = nullptr;

public:
	/*
	* 用后序析构树的存储结构（对应的二叉树）
	*/
	void traversePostOrder_for_Delete(CSTreeNode<T>* parent);

	~CSTree(){
		traversePostOrder_for_Delete(root);
	}

	/*
	* 通过创建对应的二叉树而创建树：已知对应二叉树的顺序存储，用顺序存储二叉树初始化一个二叉链表存储二叉树。
	*/
	void createCorrespondingBiTree_from_SqBiTree(SqBiTree<T>& sqBiTree, int i, CSTreeNode<T>*& parent);//定义两个特例化
	void createCorrespondingBiTree_from_SqBiTree(SqBiTree<T>& sqBiTree);//为了封装上面的同名函数，因为不能把成员变量root作为成员函数参数默认值

	/*
	* 通过创建对应的二叉树而创建树：已知树的层序序列和树的每个结点的度，创建对应二叉树。
	* 对比SeqBiTree的dataArr[](就是含null的层序序列）创建BiTree(度恒为2）
	*/
	void createCorrespondingBiTree_from_TreeLevelSeq_and_AllDegree(T* levelSeq, int* degreeArr, int len);

	/*
	* 以对应二叉树层序序列的顺序把元素输出
	*/
	void traverseLevelOrderBiTree(CSTreeNode<T>* parent);
	void traverseLevelOrderBiTree() {
		std::cout << "对应二叉树的层序遍历序列：";
		traverseLevelOrderBiTree(root);
		std::cout << std::endl;
	}

	/*
	* 获取CSTree中叶子结点数（=对应二叉树中无左孩子结点数）
	* 改编自对应二叉树的层序遍历
	*/
	int getCountTreeLeafNode();

	/*
	* 以树的层序序列的顺序把元素输出
	* 仿照二叉树的层序遍历，the trick:依次入队出队结点的所有非空结点
	* in the case of CSTree: that is 出队p,如果p->firstChild!=null,入队；沿着p->firstChild->sibling入队p->firstChild的全部非空右兄弟
	*/
	void traverseLevelOrder(CSTreeNode<T>* parent);
	void traverseLevelOrder() {
		std::cout << "树的层序遍历序列：";
		traverseLevelOrder(root);
		std::cout << std::endl;
	}

	/*
	* 求树的高度，递归方式
	* 仿照二叉树的递归方式
	*/
	int getHigh(CSTreeNode<T>* parent);
	int getHigh() {
		return getHigh(root);
	}
};






template<>
inline void CSTree<int>::createCorrespondingBiTree_from_SqBiTree(SqBiTree<int>& sqBiTree, int i, CSTreeNode<int>*& parent) {//note:不能把成员变量root作为成员函数参数默认值
	if (parent != nullptr)//初始树必须为空树，避免内存泄露
		return;
	if (sqBiTree.dataArr[i] != -1 && i <= sqBiTree.count) {
		parent = new CSTreeNode<int>;
		parent->data = sqBiTree.dataArr[i];
	}
	else
		return;
	createCorrespondingBiTree_from_SqBiTree(sqBiTree, 2 * i, parent->firstChild);
	createCorrespondingBiTree_from_SqBiTree(sqBiTree, 2 * i + 1, parent->nextSibling);
}
template<>
inline void CSTree<int>::createCorrespondingBiTree_from_SqBiTree(SqBiTree<int>& sqBiTree) {//封装一下
	createCorrespondingBiTree_from_SqBiTree(sqBiTree, 1, root);
}

/*类模板的成员函数的【全 - 部参数】特例化2*/
template<>
inline void CSTree<char>::createCorrespondingBiTree_from_SqBiTree(SqBiTree<char>& sqBiTree, int i, CSTreeNode<char>*& parent) {
	if (parent != nullptr)//初始树必须为空树，避免内存泄露
		return;
	if (sqBiTree.dataArr[i] != '*' && i <= sqBiTree.count) {
		parent = new CSTreeNode<char>;
		parent->data = sqBiTree.dataArr[i];
	}
	createCorrespondingBiTree_from_SqBiTree(sqBiTree, 2 * i, parent->firstChild);
	createCorrespondingBiTree_from_SqBiTree(sqBiTree, 2 * i + 1, parent->nextSibling);
}
template<>
inline void CSTree<char>::createCorrespondingBiTree_from_SqBiTree(SqBiTree<char>& sqBiTree) {//封装一下
	createCorrespondingBiTree_from_SqBiTree(sqBiTree, 1, root);
}

/*
* 用后序析构
*/
template<class T>
inline void CSTree<T>::traversePostOrder_for_Delete(CSTreeNode<T>* parent) {
	if (parent) {
		traversePostOrder_for_Delete(parent->firstChild);
		traversePostOrder_for_Delete(parent->nextSibling);
		delete parent;
	}
}



/*
* 通过创建对应的二叉树而创建树：已知树的层序序列和树的每个结点的度，创建对应二叉树。
* 对比SeqBiTree的dataArr[](就是含null的层序序列）创建BiTree(度恒为2）
*/
template<class T>
inline void CSTree<T>::createCorrespondingBiTree_from_TreeLevelSeq_and_AllDegree(T* levelSeq, int* degreeArr, int len) {
	if (len == 0)
		return;
	int seqIdx = 0;
	int degreeIdx = 0;
	root = new CSTreeNode<T>;
	root->data = levelSeq[seqIdx++];
	std::queue<CSTreeNode<T>*> que;
	que.push(root);
	CSTreeNode<T>* parent = nullptr;//used to accept the front()
	while (!que.empty() && seqIdx<len) {
		parent = que.front();
		que.pop();
		//在对应的二叉树中，链接在树中以parent为根的所有degreeArr[degreeIdx]个孩子
		for (int i = 1; i <= degreeArr[degreeIdx]; ++i) {
			if (i == 1) {
				parent->firstChild = new CSTreeNode<T>;
				parent->firstChild->data = levelSeq[seqIdx++];
				que.push(parent->firstChild);
				parent = parent->firstChild;//
			}
			else {
				parent->nextSibling = new CSTreeNode<T>;
				parent->nextSibling->data = levelSeq[seqIdx++];
				que.push(parent->nextSibling);
				parent = parent->nextSibling;
			}
		}
		++degreeIdx;
	}
}

/*
* 以对应二叉树层序序列的顺序把元素输出
*/
template<class T>
inline void CSTree<T>::traverseLevelOrderBiTree(CSTreeNode<T>* parent) {
	std::queue<CSTreeNode<T>*> que;
	que.push(parent);
	CSTreeNode<T>* p = nullptr;
	while (!que.empty()) {
		p = que.front();
		std::cout << p->data << ",";
		que.pop();
		if (p->firstChild)
			que.push(p->firstChild);
		if (p->nextSibling)
			que.push(p->nextSibling);
	}
}

/*
* 获取CSTree中叶子结点数（=对应二叉树中无左孩子结点数）
* 改编自对应二叉树的层序遍历
*/
template<class T>
inline int CSTree<T>::getCountTreeLeafNode() {
	std::queue<CSTreeNode<T>*> que;
	que.push(root);
	CSTreeNode<T>* p = nullptr;
	int count = 0;
	while (!que.empty()) {
		p = que.front();
		if (!p->firstChild)
			++count;
		que.pop();
		if (p->firstChild)
			que.push(p->firstChild);
		if (p->nextSibling)
			que.push(p->nextSibling);
	}
	return count;
}

/*
* 以树的层序序列的顺序把元素输出
* 仿照二叉树的层序遍历，the trick:依次入队出队结点的所有非空结点
* in the case of CSTree: that is 出队p,如果p->firstChild!=null,入队；沿着p->firstChild->sibling入队p->firstChild的全部非空右兄弟
*/
template<class T>
inline void CSTree<T>::traverseLevelOrder(CSTreeNode<T>* parent) {
	std::queue<CSTreeNode<T>*> que;
	que.push(parent);
	CSTreeNode<T>* p = nullptr;
	while (!que.empty()) {
		p = que.front();//非空才入队，出队的指针必不为null
		std::cout << p->data << ",";
		que.pop();

		p = p->firstChild;
		if (p) {
			que.push(p);
			while (p->nextSibling) {
				que.push(p->nextSibling);
				p = p->nextSibling;
			}
		}
	}
}

/*
* 求树的高度，递归方式
* 仿照二叉树的递归方式
*/
template<class T>
inline int CSTree<T>::getHigh(CSTreeNode<T>* parent) {
	if (!parent)
		return 0;
	//any node, not null, may have multiple child trees, 
	//the high of the tree whoes root is parent is the max high of its all child trees plus 1.
	CSTreeNode<T>* p = parent->firstChild;
	int maxHighChildTree = getHigh(p);
	if (!p) {//parent->firstChild=null,孩子不可能有右兄弟
		return maxHighChildTree + 1;
	}
	else {//孩子可能有右兄弟-->>求max问题
		while (p) {
			p = p->nextSibling;
			int highCurChildTree = getHigh(p);
			return maxHighChildTree > highCurChildTree ? maxHighChildTree + 1 : highCurChildTree + 1;//"+1" due to parent is not null.
		}
	}
		
}





