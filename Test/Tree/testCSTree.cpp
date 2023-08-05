#include "catch.hpp"
#include "CSTree.h"
using namespace Catch::Matchers;


TEST_CASE("testing for CSTree", "") {
	std::cout << "***testing for CSTree***" << std::endl;
	//SqBiTree<int> sqBiTree(9, 8, { 1,2,3,4,5,6,7,8 });//equals { 1,2,-1,4,5,-1,-1,8 }
	SqBiTree<int> sqBiTree(9, 8, { 1,2,-1,4,5,-1,-1,8 });
	CSTree<int> csTree;
	csTree.createCorrespondingBiTree_from_SqBiTree(sqBiTree);
	csTree.traverseLevelOrderBiTree();
	csTree.traverseLevelOrder();//do note:“树”对应的二叉树，二叉树的根无右孩子 
	CHECK(csTree.getCountTreeLeafNode() == 2);
	CHECK(csTree.getHigh() == 4);

	char levelSeq[] = "abcdefg";
	int degreeArr[] = { 2,1,2,0,1,0,0 };
	CSTree<char> csTree1;
	csTree1.createCorrespondingBiTree_from_TreeLevelSeq_and_AllDegree(levelSeq, degreeArr, 7);
	std::cout << "根据树的层序和结点度，生成的树的对应二叉树：";
	csTree1.traverseLevelOrderBiTree();
	std::cout << "check: 给的树的层序\"abcdefg\" ?= ";
	csTree1.traverseLevelOrder();
	std::cout << "***testing for CSTree***" << std::endl;
}