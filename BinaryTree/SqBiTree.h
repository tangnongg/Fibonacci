#pragma once	

#include <iostream>
#include <initializer_list>
#include <iomanip>
#include <cmath>
#include <vector>

template<class T> class CSTree;
template<class T> class ThreadBiTree;
template<class T> class BiTree;
template <class T>
class SqBiTree {
	friend class BiTree<T>;
	friend class ThreadBiTree<T>;
	friend class CSTree<T>;
private:
	T* dataArr;
	int size;//数组大小
	int count;//不是实际结点数量，而是最少花费的结点数量（含占位结点，不含dataArr[0]）,count是初始化列表中的元素个数。

public:
	SqBiTree() :
		dataArr(nullptr), size(0), count(0)
	{}

	SqBiTree(const int& size, const int& count, std::initializer_list<T> iniList);

	~SqBiTree() {
		delete [] dataArr;
	}

	void printAll();

	int getHigh() {
		if (count < 0 || count > count)
			return -1;
		return ceil(log2(count + 1));//convert double value into int value
	}

	int getHigh_of_Node(const int& num) {
		if (num < 0 || num > count)
			return -1;
		return ceil(log2(num + 1));
	}

	/*
	* graphically print the binary tree in tree form.
	*/
	void printAll_in_Tree();

	/*
	* 返回两个结点的最近公共祖先在数组中的下标(=编号）
	*/
	int getClosestCommonAncestor_of_TwoNodes(int aNodeNum, int bNodeNum);

	/*
	* 408真题
	* 是否时二叉排序树（二叉搜索树），结点全为正整数。
	* note:BST的定义是，左子树中所有node < root < 右子树中所有node
	* 正确实现：BST的中序遍历应该是严格升序的
	*/
	void traverseInOrder(int i, std::vector<int>& inSeq);
	bool isBST();
};





template<class T>
inline SqBiTree<T>::SqBiTree(const int& size, const int& count, std::initializer_list<T> iniList) :
	size(size), count(count)
{
	if (size < count + 1) {
		throw("wrong size or count!");
	}
	dataArr = new T[size];
	dataArr[0] = -1;//不用
	int index = 0;
	for (auto elem : iniList)
		dataArr[++index] = elem;
}

template<class T>
inline void SqBiTree<T>::printAll() {
	for (int i = 1; i <= count; ++i) {
		if (i != count)
			std::cout << dataArr[i] << ",";
		else
			std::cout << dataArr[i] << std::endl;
	}
}

template<class T>
inline void SqBiTree<T>::printAll_in_Tree() {
	std::cout.fill(' ');

	switch (getHigh())
	{
	case 0:
		std::cout << "no node in the tree." << std::endl;
		break;
	case 1:
		std::cout << "             " << dataArr[1] << "         " << std::endl;
		break;
	case 2:
		std::cout << "             " << std::setw(2) << dataArr[1] << "         " << std::endl;
		std::cout << "            /" << "  " << "\\" << std::endl;
		if (count == 2)
			std::cout << "           " << std::setw(2) << dataArr[2] << std::endl;
		else
			std::cout << "           " << std::setw(2) << dataArr[2] << "   " << std::setw(2) << dataArr[3] << std::endl;
		break;
	case 3:
		std::cout << "             " << std::setw(2) << dataArr[1] << "         " << std::endl;
		std::cout << "            /" << "  " << "\\" << std::endl;
		std::cout << "           " << std::setw(2) << dataArr[2] << "   " << std::setw(2) << dataArr[3] << std::endl;
		std::cout << "          /" << " " << "\\   " << "/" << " " << "\\" << std::endl;
		if (count == 4)
			std::cout << "        " << std::setw(2) << dataArr[4] << std::endl;
		else if (count == 5)
			std::cout << "        " << std::setw(2) << dataArr[4] << "  " << std::setw(2) << dataArr[5] << std::endl;
		else if (count == 6)
			std::cout << "        " << std::setw(2) << dataArr[4] << "  " << std::setw(2) << dataArr[5] << " " << std::setw(2) << dataArr[6] << std::endl;
		else
			std::cout << "        " << std::setw(2) << dataArr[4] << "  " << std::setw(2) << dataArr[5] << " " << std::setw(2) << dataArr[6] << "  " << std::setw(2) << dataArr[7] << std::endl;
		break;
	case 4:
		std::cout << "             " << std::setw(2) << dataArr[1] << "         " << std::endl;
		std::cout << "            /" << "  " << "\\" << std::endl;
		std::cout << "          /" << "      " << "\\" << std::endl;
		std::cout << "        " << std::setw(2) << dataArr[2] << "        " << std::setw(2) << dataArr[3] << std::endl;
		std::cout << "        /" << " " << "\\       " << "/" << " " << "\\" << std::endl;
		std::cout << "      " << std::setw(2) << dataArr[4] << "   " << std::setw(2) << dataArr[5] << "   " << std::setw(2) << dataArr[6] << "   " << std::setw(2) << dataArr[7] << std::endl;
		std::cout << "     /" << " " << "\\  " << "/" << " " << "\\   " << "/" << " " << "\\  " << "/" << " " << "\\" << std::endl;
		if (count == 8)
			std::cout << "   " << std::setw(2) << dataArr[8] << std::endl;
		else if (count == 9)
			std::cout << "   " << std::setw(2) << dataArr[8] << " " << std::setw(2) << dataArr[9] << std::endl;
		else if (count == 10)
			std::cout << "   " << std::setw(2) << dataArr[8] << " " << std::setw(2) << dataArr[9] << " " << std::setw(2) << dataArr[10] << std::endl;
		else if (count == 11)
			std::cout << "   " << std::setw(2) << dataArr[8] << " " << std::setw(2) << dataArr[9] << " " << std::setw(2) << dataArr[10] << " " << std::setw(2) << dataArr[11] << std::endl;
		else if (count == 12)
			std::cout << "   " << std::setw(2) << dataArr[8] << " " << std::setw(2) << dataArr[9] << " " << std::setw(2) << dataArr[10] << " " << std::setw(2) << dataArr[11]
			<< " " << std::setw(2) << dataArr[12] << std::endl;
		else if (count == 13)
			std::cout << "   " << std::setw(2) << dataArr[8] << " " << std::setw(2) << dataArr[9] << " " << std::setw(2) << dataArr[10] << " " << std::setw(2) << dataArr[11]
			<< " " << std::setw(2) << dataArr[12] << " " << std::setw(2) << dataArr[13] << std::endl;
		else if (count == 14)
			std::cout << "   " << std::setw(2) << dataArr[8] << " " << std::setw(2) << dataArr[9] << " " << std::setw(2) << dataArr[10] << " " << std::setw(2) << dataArr[11]
			<< " " << std::setw(2) << dataArr[12] << " " << std::setw(2) << dataArr[13] << " " << std::setw(2) << dataArr[14] << std::endl;
		else
			std::cout << "   " << std::setw(2) << dataArr[8] << " " << std::setw(2) << dataArr[9] << " " << std::setw(2) << dataArr[10] << " " << std::setw(2) << dataArr[11]
			<< " " << std::setw(2) << dataArr[12] << " " << std::setw(2) << dataArr[13] << " " << std::setw(2) << dataArr[14] << " " << std::setw(2) << dataArr[15] << std::endl;
		break;
	default:
		std::cout << "this function can only show a tree not more than 4 level in graphic form." << std::endl;
		break;
	}
}

/*
* 返回两个结点的最近公共祖先在数组中的下标(=编号）
*/
template<class T>
inline int SqBiTree<T>::getClosestCommonAncestor_of_TwoNodes(int aNodeNum, int bNodeNum) {
	if (aNodeNum > count || bNodeNum > count)
		return -1;
	int aNodeHigh = getHigh_of_Node(aNodeNum);
	int bNodeHigh = getHigh_of_Node(bNodeNum);
	int diff = aNodeHigh - bNodeHigh;
	while (diff > 0) {
		aNodeNum = aNodeNum / 2;
		--diff;
	}
	while (diff < 0) {
		bNodeNum = bNodeNum / 2;
		++diff;
	}
	//at the moment the two refs are at the same level, then start moving the two refs up synchronously.
	while (aNodeNum != bNodeNum) {
		aNodeNum = aNodeNum / 2;
		bNodeNum = bNodeNum / 2;
	}
	return aNodeNum;
}

/*
* 408真题
* 是否时二叉排序树（二叉搜索树），结点全为正整数。
* note:BST的定义是，左子树中所有node < root < 右子树中所有node
* 正确实现：BST的中序遍历应该是严格升序的。实现顺序存储的二叉树的中序遍历（递归）。
*/
template<class T>
inline void SqBiTree<T>::traverseInOrder(int i, std::vector<int>& inSeq) {
	if (i > count || dataArr[i] == -1)//diff:parent=null
		return;

	traverseInOrder(2 * i, inSeq);
	inSeq.push_back(dataArr[i]);
	traverseInOrder(2 * i + 1, inSeq);
}

template<class T>
inline bool SqBiTree<T>::isBST() {
	std::vector<int> inSeq;
	traverseInOrder(1, inSeq);
	for (int i = 0; i <= inSeq.size() - 2; ++i) {
		if (inSeq[i] >= inSeq[i + 1])
			return false;
	}
	return true;
}

