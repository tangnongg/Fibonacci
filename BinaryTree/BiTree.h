#pragma once

#include "SqBiTree.h"
//#include <Queue>//���������Ĳ�������е�Ӧ��
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
	* �ú�������
	*/
	void traversePostOrder_for_Delete(BiNode<T>* parent);

	/*
	 * ֻ���ú������ȥ�ͷ����еĽ�㣬��ͬ��ֻ�������ͷţ��ͷ�֮�����ָ����Ҳ���ʲ��ˡ�
	*/
	~BiTree()
	{
		traversePostOrder_for_Delete(root);
	}

	const int& getCount() {
		return count;
	}

	/*
	* ��˳��洢��������ʼ��һ����������洢������
	*/
	void createBiTree_from_SqBiTree(SqBiTree<T>& sqBiTree, int i, BiNode<T>*& parent);//��������������
	void createBiTree_from_SqBiTree(SqBiTree<T>& sqBiTree);//Ϊ�˷�װ�����ͬ����������Ϊ���ܰѳ�Ա����root��Ϊ��Ա��������Ĭ��ֵ

	/*
	* ���������е�˳���Ԫ�����
	*/
	void traversePreOrder(BiNode<T>* parent);
	void traversePreOrder() {
		std::cout << "����������У�";
		traversePreOrder(root);
		std::cout << std::endl;
	}

	/*
	* ���������е�˳���Ԫ�طŵ�vector��
	*/
	void printAlltoVecPreOrder(BiNode<T>* parent, std::vector<T>& vec);
	void printAlltoVecPreOrder(std::vector<T>& vec) {
		printAlltoVecPreOrder(root, vec);
	}

	/*
	* �Բ������е�˳���Ԫ�����
	*/
	void traverseLevelOrder(BiNode<T>* parent);
	void traverseLevelOrder() {
		std::cout << "����������У�";
		traverseLevelOrder(root);
		std::cout << std::endl;
	}

	/*
	* �Ժ������е�˳���Ԫ�����
	*/
	void traversePostOrder(BiNode<T>* parent);
	void traversePostOrder() {
		std::cout << "����������У�";
		traversePostOrder(root);
		std::cout << std::endl;
	}

	/*
	* �ǵݹ�������
	*/
	void traversePostOrder_NonRecursive(BiNode<T>* parent);
	void traversePostOrder_NonRecursive() {
		std::cout << "�ǵݹ����������У�";	
		traversePostOrder_NonRecursive(root);
		std::cout << std::endl;
	}

	/*
	* �ı�ǵݹ�����������ȡ���Ƚ�㵽�������·��
	*/
	void getPath_fromAncestortoDescendant(BiNode<T>* ancestor, T descendant, std::vector<T>& retVec);
	void getPath_fromAncestortoDescendant(T descendant, std::vector<T>& retVec) {
		getPath_fromAncestortoDescendant(root, descendant, retVec);
	}

	/*
	* ��������ĸ߶ȣ��ݹ鷽ʽ
	*/
	int getHigh(BiNode<T>* parent);
	int getHigh() {
		return getHigh(root);
	}

	/*
	* �ı�ǵݹ�����������������ĸ߶�
	*/
	int getHigh_PostOrder_NonRecursive(BiNode<T>* parent);
	int getHigh_PostOrder_NonRecursive() {
		return getHigh_PostOrder_NonRecursive(root);
	}
};








/*��ģ��ĳ�Ա�����ġ�ȫ - ��������������1 */
template<>
inline void BiTree<int>::createBiTree_from_SqBiTree(SqBiTree<int>& sqBiTree, int i, BiNode<int>*& parent) {//note:���ܰѳ�Ա����root��Ϊ��Ա��������Ĭ��ֵ
	if (parent != nullptr)//��ʼ������Ϊ�����������ڴ�й¶
		return;
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

/*��ģ��ĳ�Ա�����ġ�ȫ - ��������������2*/
template<>
inline void BiTree<char>::createBiTree_from_SqBiTree(SqBiTree<char>& sqBiTree, int i, BiNode<char>*& parent) {
	if (parent != nullptr)//��ʼ������Ϊ�����������ڴ�й¶
		return;
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
/*
* ���������е�˳���Ԫ�����
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
* �ú�������
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
* ��ǰ�����е�˳���Ԫ�طŵ�vector��
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
* �Բ������е�˳���Ԫ�����
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
* �Ժ������е�˳���Ԫ�����
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
* �ǵݹ�������
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
* �ı�ǵݹ�����������ȡ���Ƚ�㵽�������·��
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
* ��������ĸ߶ȣ��ݹ鷽ʽ
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
* �ı�ǵݹ�����������������ĸ߶�
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






