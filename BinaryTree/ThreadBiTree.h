#pragma once
#include "SqBiTree.h"

/**********************************
*    ThreadBiNode����������
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

	void createBiTree_from_SqBiTree(SqBiTree<T>& sqBiTree, int i, ThreadBiNode<T>*& parent);//����1��������
	void createBiTree_from_SqBiTree(SqBiTree<T>& sqBiTree);//Ϊ�˷�װ�����ͬ����������Ϊ���ܰѳ�Ա����root��Ϊ��Ա��������Ĭ��ֵ

	/*
	 * ��������������ȥ�ͷ����еĽ��
	*/
	~ThreadBiTree();

	/*
	 *������� infix order
	*/
	void traverseInOrder(ThreadBiNode<T>*& parent);
	void traverseInOrder();

	/*
	 *����������(recursive)
	 * input:p, the working pointer to the current node; pre, the pointer to the previous node just visited.
	*/
	void thread(ThreadBiNode<T>*& p, ThreadBiNode<T>*& pre);
	void thread() {
		ThreadBiNode<T>* pre = nullptr;
		thread(root, pre);// err: cannot convert argument 2 from 'nullptr' to 'ThreadBiNode<T> *&
		//do note:�������һ�����ĺ��û�д���ֻ����ǰһ������������������;---->>����ʼ��ʱĬ��Ϊtrue.
	}
	/*
	 *���������������������������õ������������
	*/
	void traverse_by_InfixThread();
};





/*��ģ��ĳ�Ա�����ġ�ȫ - ��������������1 */
template<>
inline void ThreadBiTree<int>::createBiTree_from_SqBiTree(SqBiTree<int>& sqBiTree, int i, ThreadBiNode<int>*& parent) {//note:���ܰѳ�Ա����root��Ϊ��Ա��������Ĭ��ֵ
	if (parent != nullptr)//��ʼ������Ϊ�����������ڴ�й¶
		return;
	if (sqBiTree.dataArr[i] != -1 && i <= sqBiTree.count)
		parent = new ThreadBiNode<int>(sqBiTree.dataArr[i], nullptr, nullptr, false, false);
	else
		return;
	createBiTree_from_SqBiTree(sqBiTree, 2 * i, (parent->lchild));
	createBiTree_from_SqBiTree(sqBiTree, 2 * i + 1, (parent->rchild));
}
template<>
inline void ThreadBiTree<int>::createBiTree_from_SqBiTree(SqBiTree<int>& sqBiTree) {//��װһ��
	createBiTree_from_SqBiTree(sqBiTree, 1, root);
	count = sqBiTree.count;
	std::cout << "before thread():";//������Բ鿴
	traverseInOrder();
	thread();//�����������������ͳһ������������ͨ������������!=����������������
}

/*
* ��������������ȥ�ͷ����еĽ��
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
*������� infix order
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
	std::cout << "�������У�";
	traverseInOrder(root);
	std::cout << std::endl;
}

/*
*����������(recursive)
* input:p, the working pointer to the current node; pre, the pointer to the previous node just visited.
*/
template<class T>
inline void ThreadBiTree<T>::thread(ThreadBiNode<T>*& p, ThreadBiNode<T>*& pre) {
	if (p) {
		thread(p->lchild, pre);

		if (p->lchild == nullptr) {//���õ�ǰ��������ǰ������
			p->ltag = true;
			p->lchild = pre;
		}
		if (pre != nullptr && pre->rchild == nullptr) {//����ǰһ����������������
			pre->rtag = true;
			pre->rchild = p;
		}
		pre = p;//����pre

		thread(p->rchild, pre);
	}
}

/*
*���������������������������õ������������
*/
template<class T>
inline void ThreadBiTree<T>::traverse_by_InfixThread() {
	//get��������ĵ�һ��node
	ThreadBiNode<T>* p = root;
	while (p->lchild)
		p = p->lchild;
	//�����p node����
	while (p) {
		std::cout << p->data << ",";	
		if (p->rtag == true)		
			p = p->rchild;
		else  {//�������������,��get��������������ĵ�һ��node
			p = p->rchild;
			while (p && p->ltag==false)//�������Ѿ���������Ҫ��������(&& p->lchild) 
				p = p->lchild;
		}
		
	}
	std::cout << std::endl;
}
