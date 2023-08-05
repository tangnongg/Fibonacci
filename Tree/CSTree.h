#pragma once

#include "SqBiTree.h"
#include <vector>
#include <iostream>
#include <queue>

/*******************************************
*	����㣨�����ֵܱ�ʾ����i.e.��������ʾ����
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
*	���������ֵܱ�ʾ����i.e.��������ʾ����
*   �����Ӧ������---->>��������
********************************************/
template<class T>
class CSTree
{
private:
	CSTreeNode<T>* root = nullptr;

public:
	/*
	* �ú����������Ĵ洢�ṹ����Ӧ�Ķ�������
	*/
	void traversePostOrder_for_Delete(CSTreeNode<T>* parent);

	~CSTree(){
		traversePostOrder_for_Delete(root);
	}

	/*
	* ͨ��������Ӧ�Ķ�����������������֪��Ӧ��������˳��洢����˳��洢��������ʼ��һ����������洢��������
	*/
	void createCorrespondingBiTree_from_SqBiTree(SqBiTree<T>& sqBiTree, int i, CSTreeNode<T>*& parent);//��������������
	void createCorrespondingBiTree_from_SqBiTree(SqBiTree<T>& sqBiTree);//Ϊ�˷�װ�����ͬ����������Ϊ���ܰѳ�Ա����root��Ϊ��Ա��������Ĭ��ֵ

	/*
	* ͨ��������Ӧ�Ķ�����������������֪���Ĳ������к�����ÿ�����Ķȣ�������Ӧ��������
	* �Ա�SeqBiTree��dataArr[](���Ǻ�null�Ĳ������У�����BiTree(�Ⱥ�Ϊ2��
	*/
	void createCorrespondingBiTree_from_TreeLevelSeq_and_AllDegree(T* levelSeq, int* degreeArr, int len);

	/*
	* �Զ�Ӧ�������������е�˳���Ԫ�����
	*/
	void traverseLevelOrderBiTree(CSTreeNode<T>* parent);
	void traverseLevelOrderBiTree() {
		std::cout << "��Ӧ�������Ĳ���������У�";
		traverseLevelOrderBiTree(root);
		std::cout << std::endl;
	}

	/*
	* ��ȡCSTree��Ҷ�ӽ������=��Ӧ�������������ӽ������
	* �ı��Զ�Ӧ�������Ĳ������
	*/
	int getCountTreeLeafNode();

	/*
	* �����Ĳ������е�˳���Ԫ�����
	* ���ն������Ĳ��������the trick:������ӳ��ӽ������зǿս��
	* in the case of CSTree: that is ����p,���p->firstChild!=null,��ӣ�����p->firstChild->sibling���p->firstChild��ȫ���ǿ����ֵ�
	*/
	void traverseLevelOrder(CSTreeNode<T>* parent);
	void traverseLevelOrder() {
		std::cout << "���Ĳ���������У�";
		traverseLevelOrder(root);
		std::cout << std::endl;
	}

	/*
	* �����ĸ߶ȣ��ݹ鷽ʽ
	* ���ն������ĵݹ鷽ʽ
	*/
	int getHigh(CSTreeNode<T>* parent);
	int getHigh() {
		return getHigh(root);
	}
};






template<>
inline void CSTree<int>::createCorrespondingBiTree_from_SqBiTree(SqBiTree<int>& sqBiTree, int i, CSTreeNode<int>*& parent) {//note:���ܰѳ�Ա����root��Ϊ��Ա��������Ĭ��ֵ
	if (parent != nullptr)//��ʼ������Ϊ�����������ڴ�й¶
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
inline void CSTree<int>::createCorrespondingBiTree_from_SqBiTree(SqBiTree<int>& sqBiTree) {//��װһ��
	createCorrespondingBiTree_from_SqBiTree(sqBiTree, 1, root);
}

/*��ģ��ĳ�Ա�����ġ�ȫ - ��������������2*/
template<>
inline void CSTree<char>::createCorrespondingBiTree_from_SqBiTree(SqBiTree<char>& sqBiTree, int i, CSTreeNode<char>*& parent) {
	if (parent != nullptr)//��ʼ������Ϊ�����������ڴ�й¶
		return;
	if (sqBiTree.dataArr[i] != '*' && i <= sqBiTree.count) {
		parent = new CSTreeNode<char>;
		parent->data = sqBiTree.dataArr[i];
	}
	createCorrespondingBiTree_from_SqBiTree(sqBiTree, 2 * i, parent->firstChild);
	createCorrespondingBiTree_from_SqBiTree(sqBiTree, 2 * i + 1, parent->nextSibling);
}
template<>
inline void CSTree<char>::createCorrespondingBiTree_from_SqBiTree(SqBiTree<char>& sqBiTree) {//��װһ��
	createCorrespondingBiTree_from_SqBiTree(sqBiTree, 1, root);
}

/*
* �ú�������
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
* ͨ��������Ӧ�Ķ�����������������֪���Ĳ������к�����ÿ�����Ķȣ�������Ӧ��������
* �Ա�SeqBiTree��dataArr[](���Ǻ�null�Ĳ������У�����BiTree(�Ⱥ�Ϊ2��
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
		//�ڶ�Ӧ�Ķ������У�������������parentΪ��������degreeArr[degreeIdx]������
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
* �Զ�Ӧ�������������е�˳���Ԫ�����
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
* ��ȡCSTree��Ҷ�ӽ������=��Ӧ�������������ӽ������
* �ı��Զ�Ӧ�������Ĳ������
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
* �����Ĳ������е�˳���Ԫ�����
* ���ն������Ĳ��������the trick:������ӳ��ӽ������зǿս��
* in the case of CSTree: that is ����p,���p->firstChild!=null,��ӣ�����p->firstChild->sibling���p->firstChild��ȫ���ǿ����ֵ�
*/
template<class T>
inline void CSTree<T>::traverseLevelOrder(CSTreeNode<T>* parent) {
	std::queue<CSTreeNode<T>*> que;
	que.push(parent);
	CSTreeNode<T>* p = nullptr;
	while (!que.empty()) {
		p = que.front();//�ǿղ���ӣ����ӵ�ָ��ز�Ϊnull
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
* �����ĸ߶ȣ��ݹ鷽ʽ
* ���ն������ĵݹ鷽ʽ
*/
template<class T>
inline int CSTree<T>::getHigh(CSTreeNode<T>* parent) {
	if (!parent)
		return 0;
	//any node, not null, may have multiple child trees, 
	//the high of the tree whoes root is parent is the max high of its all child trees plus 1.
	CSTreeNode<T>* p = parent->firstChild;
	int maxHighChildTree = getHigh(p);
	if (!p) {//parent->firstChild=null,���Ӳ����������ֵ�
		return maxHighChildTree + 1;
	}
	else {//���ӿ��������ֵ�-->>��max����
		while (p) {
			p = p->nextSibling;
			int highCurChildTree = getHigh(p);
			return maxHighChildTree > highCurChildTree ? maxHighChildTree + 1 : highCurChildTree + 1;//"+1" due to parent is not null.
		}
	}
		
}





