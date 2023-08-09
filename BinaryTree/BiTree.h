#pragma once

#include "SqBiTree.h"
//#include <Queue>//队列在树的层序遍历中的应用
//#include "Queue.h"//vs is shit!!
#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>//std::reverse()
#include <queue>


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

	/*
	* generate the tree according to preSeq and inSeq
	* the trick:两次划分左右子树（子序列），一次在中序，一次在前序。
	* input:前序和中序元素值序列，由于要查找root在中序中的位置，故假设元素值无重复。输入数组从1开始存放（对本题无益处）
	*/
	void generateBiTree_Pre_and_In(T* preSeq, int sPre, int ePre, T* inSeq, int sIn, int eIn, BiNode<T>*& parent);
	void generateBiTree_Pre_and_In(T* preSeq, int sPre, int ePre, T* inSeq, int sIn, int eIn) {
		generateBiTree_Pre_and_In(preSeq, sPre, ePre, inSeq, sIn, eIn, root);
	}

	/*
	* 判断二叉树（链式存储）是不是完全二叉树
	* 仿照顺序存储的方法，在层序序列中第一个出现的null结点之后是否还有非null结点。
	*/
	bool isCompleteBinaryTree();
	
	/*
	* 获得包含“null”的层序遍历序列
	* 改编自层序遍历，改变孩子入队条件，出队判队头是否为null
	*/
	void getPostSeqIncludingNull_TraverseLevelOrder(std::vector<T>& postSeqVec);

	/*
	* 获得双分支结点的数目
	*/
	int getNodeCountDegree2(BiNode<T>* parent);
	int getNodeCountDegree2() {
		return getNodeCountDegree2(root);
	}

	/*
	* 交换所有结点的左右子树
	*/
	void swap(BiNode<T>* parent);
	void swap() {
		swap(root);
	}

	/*
	* 非递归先序遍历，获取先序遍历第K个结点的值
	*/
	const T& getKth_PreOrder(int k);

	/*
	* 递归，对于每个值为X的结点，删除以它为根的子树，并释放相应空间
	*/
	void deleteSubTreeRootedNodeX(BiNode<T>* parent, const T& x);
	void deleteSubTreeRootedNodeX(const T& x) {
		if (root->data == x) {//上面那种方法忽略了root—>data的判断，这里补上
			traversePostOrder_for_Delete(root);
			root = nullptr;
			return;
		}
		deleteSubTreeRootedNodeX(root, x);
	}

	/*
	* 实现方法2，用引用，就不用隔一层判断data==x
	* 递归，对于每个值为X的结点，删除以它为根的子树，并释放相应空间
	*/
	void deleteSubTreeRootedNodeX_Implement2_with_Ref(BiNode<T>*& parent, const T& x);
	void deleteSubTreeRootedNodeX_Implement2_with_Ref(const T& x) {
		deleteSubTreeRootedNodeX_Implement2_with_Ref(root, x);
	}

	/*
	* p,q的最近公共祖先
	* 假设元素值唯一，传入指针，返回指针的形式不便于测试
	*/
	const T& getClosestCommonAncestor_of_TwoNodes(const T& p, const T& q);

	/*
	* 二叉树的宽度
	* the trick: 迭代in, out
	*/
	int getWidth(); 
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
	if (!parent)
		return;
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
				recent = p;
				p = nullptr;
			}
		}
	}
	return maxStkDeepth;
}

/*
* generate the tree according to preSeq and inSeq
* the trick:两次划分左右子树（子序列），一次在中序，一次在前序。
* input:前序和中序元素值序列，由于要查找root在中序中的位置，故假设元素值无重复。输入数组从1开始存放（对本题无益处）
*/
template<class T>
inline void BiTree<T>::generateBiTree_Pre_and_In(T* preSeq, int sPre, int ePre, T* inSeq, int sIn, int eIn, BiNode<T>*& parent) {
	parent = new BiNode<T>(preSeq[sPre], nullptr, nullptr);
	int rootIdx_in_InSeq = 1;
	while (parent->data != inSeq[rootIdx_in_InSeq])
		++rootIdx_in_InSeq;
	int lenLSeq = (rootIdx_in_InSeq - 1) - sIn + 1;
	int lenRSeq = eIn - (rootIdx_in_InSeq + 1) + 1;
	//rootIdx_in_InSeq， lenLSeq， lenRSeq
	if (lenLSeq)
		generateBiTree_Pre_and_In(preSeq, sPre + 1, sPre + lenLSeq, inSeq, sIn, rootIdx_in_InSeq - 1, parent->lchild);
	if (lenRSeq)
		generateBiTree_Pre_and_In(preSeq, sPre + lenLSeq + 1, ePre, inSeq, rootIdx_in_InSeq + 1, eIn, parent->rchild);
}

/*
* 判断二叉树（链式存储）是不是完全二叉树
* 仿照顺序存储的方法，在层序序列中第一个出现的null结点之后是否还有非null结点。
*/
template<class T>
inline bool BiTree<T>::isCompleteBinaryTree() {
	std::vector<T> postSeqVec;
	getPostSeqIncludingNull_TraverseLevelOrder(postSeqVec);
	bool fundNull = false;
	for (const auto& elem : postSeqVec) {
		if (elem == -1 && fundNull == false) {//第一次发现-1，标记fundNull=true
			fundNull = true;
			//continue;//在后续中找，跳过本轮,不是必要
		}
		if (elem != -1 && fundNull == true)//在fundNull=true的条件下，发现后序有非-1出现
			return false;
	}
	return true;
}

/*
* 获得包含“null”的层序遍历序列
* 改编自层序遍历，改变孩子入队条件，出队判队头是否为null
*/
template<class T>
inline void BiTree<T>::getPostSeqIncludingNull_TraverseLevelOrder(std::vector<T>& postSeqVec) {
	Queue<BiNode<T>*> que(100);
	que.push(root);
	BiNode<T>* p = nullptr;
	while (!que.empty()) {
		p = que.front();
		que.pop();
		//对出队结点判Null,非Null时，直接入队左右孩子（无论是否Null）
		if (p) {
			que.push(p->lchild);
			que.push(p->rchild);
			postSeqVec.push_back(p->data);
		}
		else
			postSeqVec.push_back(-1);//-1 means this node does not exist, just for filling this place.
	}
}

/*
* 获得双分支结点的数目
*/
template<class T>
inline int BiTree<T>::getNodeCountDegree2(BiNode<T>* parent) {
	if (!parent)//先指针判空
		return 0;
	if (parent->lchild && parent->rchild)
		return 1 + getNodeCountDegree2(parent->lchild) + getNodeCountDegree2(parent->rchild);
	else
		return 0 + getNodeCountDegree2(parent->lchild) + getNodeCountDegree2(parent->rchild);
}

/*
* 交换所有结点的左右子树
*/
template<class T>
inline void BiTree<T>::swap(BiNode<T>* parent) {
	if (!parent)
		return;
	std::swap<BiNode<T>*>(parent->lchild, parent->rchild);
	swap(parent->lchild);
	swap(parent->rchild);
}

/*
* 非递归先序遍历，获取先序遍历第K个结点的值
*/
template<class T>
inline const T& BiTree<T>::getKth_PreOrder(int k) {
	BiNode<T>* p = root;
	std::stack<BiNode<T>*> stk;
	int cnt = 1;
	while (p || !stk.empty()) {
		if (p) {
			stk.push(p);
			if (cnt == k) {
				return p->data;
			}
			++cnt;
			p = p->lchild;
		}
		else {
			p = stk.top();
			stk.pop();
			p = p->rchild;
		}
	}
}

/*
* 递归，对于每个值为X的结点，删除以它为根的子树，并释放相应空间
*/
template<class T>
inline void BiTree<T>::deleteSubTreeRootedNodeX(BiNode<T>* parent, const T& x) {
	if (!parent)
		return;

	if (parent->lchild && parent->lchild->data == x) {//而不是判断parent.data==x, 为可能的删除操作保留parent
		traversePostOrder_for_Delete(parent->lchild);
		parent->lchild = nullptr;
	}
	else {
		deleteSubTreeRootedNodeX(parent->lchild, x);
	}
	if (parent->rchild && parent->rchild->data == x) {
		traversePostOrder_for_Delete(parent->rchild);
		parent->rchild = nullptr;
	}
	else {
		deleteSubTreeRootedNodeX(parent->rchild, x);
	}
}

/*
* 实现方法2，用引用，就不用隔一层判断data==x
* 递归，对于每个值为X的结点，删除以它为根的子树，并释放相应空间
*/
template<class T>
inline void BiTree<T>::deleteSubTreeRootedNodeX_Implement2_with_Ref(BiNode<T>*& parent, const T& x) {
	if (!parent)
		return;

	if (parent->data == x) {//而不是判断parent.data==x, 为可能的删除操作保留parent
		traversePostOrder_for_Delete(parent);
		parent = nullptr;
	}
	else {
		deleteSubTreeRootedNodeX_Implement2_with_Ref(parent->lchild, x);
		deleteSubTreeRootedNodeX_Implement2_with_Ref(parent->rchild, x);
	}
}

/*
* p,q的最近公共祖先
* 假设元素值唯一，传入指针，返回指针的形式不便于测试
*/
template<class T>
inline const T& BiTree<T>::getClosestCommonAncestor_of_TwoNodes(const T& p, const T& q) {
	std::vector<T> pathVecP;
	std::vector<T> pathVecQ;
	getPath_fromAncestortoDescendant(root, p, pathVecP);
	getPath_fromAncestortoDescendant(root, q, pathVecQ);
	std::reverse(pathVecP.begin(), pathVecP.end());
	std::reverse(pathVecQ.begin(), pathVecQ.end());

	std::vector<T>::iterator itp = pathVecP.begin();
	std::vector<T>::iterator itq = pathVecQ.begin();
	T pre = T();
	for (; itp != pathVecP.end() && itq != pathVecQ.end(); ++itp, ++itq) {
		if (*itp == *itq)
			pre = *itp;
		else
			return pre;
	}
	throw "无公共结点, p and q does not exist in the same tree.";
}

/*
* 二叉树的宽度
* the trick: 迭代in, out
*/
template<class T>
inline int BiTree<T>::getWidth() {
	BiNode<T>* p = root;
	std::queue<BiNode<T>*> que;
	if (p)
		que.push(p);
	else
		return 0;
	/*initial in and out*/
	int in = 1;//这（root)层入队的孩子结点数
	int out = 0;//把上一层（上层入队的孩子）结点全出队（out=in)，把这层出队结点的孩子再入队
	int maxIn = in;
	while (!que.empty()) {
		if (out == 0) {//update
			out = in;
			if (in > maxIn)
				maxIn = in;
			in = 0;
		}
		p = que.front();
		que.pop();
		--out;
		if (p->lchild)
		{
			que.push(p->lchild);
			++in;
		}
		if (p->rchild) {
			que.push(p->rchild);
			++in;
		}
	}
	return maxIn;
}