#pragma once

#include "SqBiTree.h"
//#include <Queue>//���������Ĳ�������е�Ӧ��
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

	/*
	* generate the tree according to preSeq and inSeq
	* the trick:���λ������������������У���һ��������һ����ǰ��
	* input:ǰ�������Ԫ��ֵ���У�����Ҫ����root�������е�λ�ã��ʼ���Ԫ��ֵ���ظ������������1��ʼ��ţ��Ա������洦��
	*/
	void generateBiTree_Pre_and_In(T* preSeq, int sPre, int ePre, T* inSeq, int sIn, int eIn, BiNode<T>*& parent);
	void generateBiTree_Pre_and_In(T* preSeq, int sPre, int ePre, T* inSeq, int sIn, int eIn) {
		generateBiTree_Pre_and_In(preSeq, sPre, ePre, inSeq, sIn, eIn, root);
	}

	/*
	* �ж϶���������ʽ�洢���ǲ�����ȫ������
	* ����˳��洢�ķ������ڲ��������е�һ�����ֵ�null���֮���Ƿ��з�null��㡣
	*/
	bool isCompleteBinaryTree();
	
	/*
	* ��ð�����null���Ĳ����������
	* �ı��Բ���������ı亢����������������ж�ͷ�Ƿ�Ϊnull
	*/
	void getPostSeqIncludingNull_TraverseLevelOrder(std::vector<T>& postSeqVec);

	/*
	* ���˫��֧������Ŀ
	*/
	int getNodeCountDegree2(BiNode<T>* parent);
	int getNodeCountDegree2() {
		return getNodeCountDegree2(root);
	}

	/*
	* �������н�����������
	*/
	void swap(BiNode<T>* parent);
	void swap() {
		swap(root);
	}

	/*
	* �ǵݹ������������ȡ���������K������ֵ
	*/
	const T& getKth_PreOrder(int k);

	/*
	* �ݹ飬����ÿ��ֵΪX�Ľ�㣬ɾ������Ϊ�������������ͷ���Ӧ�ռ�
	*/
	void deleteSubTreeRootedNodeX(BiNode<T>* parent, const T& x);
	void deleteSubTreeRootedNodeX(const T& x) {
		if (root->data == x) {//�������ַ���������root��>data���жϣ����ﲹ��
			traversePostOrder_for_Delete(root);
			root = nullptr;
			return;
		}
		deleteSubTreeRootedNodeX(root, x);
	}

	/*
	* ʵ�ַ���2�������ã��Ͳ��ø�һ���ж�data==x
	* �ݹ飬����ÿ��ֵΪX�Ľ�㣬ɾ������Ϊ�������������ͷ���Ӧ�ռ�
	*/
	void deleteSubTreeRootedNodeX_Implement2_with_Ref(BiNode<T>*& parent, const T& x);
	void deleteSubTreeRootedNodeX_Implement2_with_Ref(const T& x) {
		deleteSubTreeRootedNodeX_Implement2_with_Ref(root, x);
	}

	/*
	* p,q�������������
	* ����Ԫ��ֵΨһ������ָ�룬����ָ�����ʽ�����ڲ���
	*/
	const T& getClosestCommonAncestor_of_TwoNodes(const T& p, const T& q);

	/*
	* �������Ŀ��
	* the trick: ����in, out
	*/
	int getWidth(); 
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
				recent = p;
				p = nullptr;
			}
		}
	}
	return maxStkDeepth;
}

/*
* generate the tree according to preSeq and inSeq
* the trick:���λ������������������У���һ��������һ����ǰ��
* input:ǰ�������Ԫ��ֵ���У�����Ҫ����root�������е�λ�ã��ʼ���Ԫ��ֵ���ظ������������1��ʼ��ţ��Ա������洦��
*/
template<class T>
inline void BiTree<T>::generateBiTree_Pre_and_In(T* preSeq, int sPre, int ePre, T* inSeq, int sIn, int eIn, BiNode<T>*& parent) {
	parent = new BiNode<T>(preSeq[sPre], nullptr, nullptr);
	int rootIdx_in_InSeq = 1;
	while (parent->data != inSeq[rootIdx_in_InSeq])
		++rootIdx_in_InSeq;
	int lenLSeq = (rootIdx_in_InSeq - 1) - sIn + 1;
	int lenRSeq = eIn - (rootIdx_in_InSeq + 1) + 1;
	//rootIdx_in_InSeq�� lenLSeq�� lenRSeq
	if (lenLSeq)
		generateBiTree_Pre_and_In(preSeq, sPre + 1, sPre + lenLSeq, inSeq, sIn, rootIdx_in_InSeq - 1, parent->lchild);
	if (lenRSeq)
		generateBiTree_Pre_and_In(preSeq, sPre + lenLSeq + 1, ePre, inSeq, rootIdx_in_InSeq + 1, eIn, parent->rchild);
}

/*
* �ж϶���������ʽ�洢���ǲ�����ȫ������
* ����˳��洢�ķ������ڲ��������е�һ�����ֵ�null���֮���Ƿ��з�null��㡣
*/
template<class T>
inline bool BiTree<T>::isCompleteBinaryTree() {
	std::vector<T> postSeqVec;
	getPostSeqIncludingNull_TraverseLevelOrder(postSeqVec);
	bool fundNull = false;
	for (const auto& elem : postSeqVec) {
		if (elem == -1 && fundNull == false) {//��һ�η���-1�����fundNull=true
			fundNull = true;
			//continue;//�ں������ң���������,���Ǳ�Ҫ
		}
		if (elem != -1 && fundNull == true)//��fundNull=true�������£����ֺ����з�-1����
			return false;
	}
	return true;
}

/*
* ��ð�����null���Ĳ����������
* �ı��Բ���������ı亢����������������ж�ͷ�Ƿ�Ϊnull
*/
template<class T>
inline void BiTree<T>::getPostSeqIncludingNull_TraverseLevelOrder(std::vector<T>& postSeqVec) {
	Queue<BiNode<T>*> que(100);
	que.push(root);
	BiNode<T>* p = nullptr;
	while (!que.empty()) {
		p = que.front();
		que.pop();
		//�Գ��ӽ����Null,��Nullʱ��ֱ��������Һ��ӣ������Ƿ�Null��
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
* ���˫��֧������Ŀ
*/
template<class T>
inline int BiTree<T>::getNodeCountDegree2(BiNode<T>* parent) {
	if (!parent)//��ָ���п�
		return 0;
	if (parent->lchild && parent->rchild)
		return 1 + getNodeCountDegree2(parent->lchild) + getNodeCountDegree2(parent->rchild);
	else
		return 0 + getNodeCountDegree2(parent->lchild) + getNodeCountDegree2(parent->rchild);
}

/*
* �������н�����������
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
* �ǵݹ������������ȡ���������K������ֵ
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
* �ݹ飬����ÿ��ֵΪX�Ľ�㣬ɾ������Ϊ�������������ͷ���Ӧ�ռ�
*/
template<class T>
inline void BiTree<T>::deleteSubTreeRootedNodeX(BiNode<T>* parent, const T& x) {
	if (!parent)
		return;

	if (parent->lchild && parent->lchild->data == x) {//�������ж�parent.data==x, Ϊ���ܵ�ɾ����������parent
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
* ʵ�ַ���2�������ã��Ͳ��ø�һ���ж�data==x
* �ݹ飬����ÿ��ֵΪX�Ľ�㣬ɾ������Ϊ�������������ͷ���Ӧ�ռ�
*/
template<class T>
inline void BiTree<T>::deleteSubTreeRootedNodeX_Implement2_with_Ref(BiNode<T>*& parent, const T& x) {
	if (!parent)
		return;

	if (parent->data == x) {//�������ж�parent.data==x, Ϊ���ܵ�ɾ����������parent
		traversePostOrder_for_Delete(parent);
		parent = nullptr;
	}
	else {
		deleteSubTreeRootedNodeX_Implement2_with_Ref(parent->lchild, x);
		deleteSubTreeRootedNodeX_Implement2_with_Ref(parent->rchild, x);
	}
}

/*
* p,q�������������
* ����Ԫ��ֵΨһ������ָ�룬����ָ�����ʽ�����ڲ���
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
	throw "�޹������, p and q does not exist in the same tree.";
}

/*
* �������Ŀ��
* the trick: ����in, out
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
	int in = 1;//�⣨root)����ӵĺ��ӽ����
	int out = 0;//����һ�㣨�ϲ���ӵĺ��ӣ����ȫ���ӣ�out=in)���������ӽ��ĺ��������
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