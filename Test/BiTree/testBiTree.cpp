#include "catch.hpp"
#include "BiTree.h"
using namespace Catch::Matchers;
#include "Queue.h"

TEST_CASE("testing for basic operations of BiTree", "") {
	SECTION("part 1") {
		SqBiTree<int> sqBiTree(4, 3, { 1,2,3 });
		BiTree<int> biTree;
		biTree.createBiTree_from_SqBiTree(sqBiTree);

		//biTree.traversePreOrder();
		std::vector<int> biTreeVec;
		biTree.printAlltoVecPreOrder(biTreeVec);
		std::vector<int> targetVec;
		targetVec.assign({ 1,2,3 });
		CHECK_THAT(biTreeVec, Equals(targetVec));
		CHECK(biTree.getCount() == 3);
	}

	//SECTION("part 2") {
	//	SqBiTree<int> sqBiTree(8, 7, { 1,-1,3,-1,-1,6,7 });
	//	BiTree<int> biTree;
	//	biTree.createBiTree_from_SqBiTree(sqBiTree);
	//	biTree.traversePostOrder();
	//}
}

TEST_CASE("testing for traversePostOrder_NonRecursive member function of BiTree", "") {
	SqBiTree<int> sqBiTree1(9, 8, { 1,2,3,4,5,6,7,8 });
	BiTree<int> biTree1;
	biTree1.createBiTree_from_SqBiTree(sqBiTree1);
	std::vector<int> pathVec;
	biTree1.getPath_fromAncestortoDescendant(8, pathVec);
	std::vector<int> targetVec;
	targetVec.assign({ 8,4,2,1 });
	CHECK_THAT(targetVec, Equals(pathVec));
}

TEST_CASE("testing for member functions of BiTree, traverseLevelOrder and two versions of getHigh", "") {
	SqBiTree<int> sqBiTree1(9, 8, { 1,2,3,4,5,6,7,8 });
	BiTree<int> biTree1;
	biTree1.createBiTree_from_SqBiTree(sqBiTree1);
	//biTree1.traverseLevelOrder();

	CHECK(4 == biTree1.getHigh());
	CHECK(4 == biTree1.getHigh_PostOrder_NonRecursive());
}

TEST_CASE("testing for member functions of BiTree, generateBiTree_Pre_and_In", "") {
	int preSeq[] = {0,1,2,4,5,6,3};
	int inSeq[] = {0,4,2,6,5,1,3};
	BiTree<int> biTree;
	biTree.generateBiTree_Pre_and_In(preSeq, 1, 6, inSeq, 1, 6);
	//biTree.traverseLevelOrder();
	std::vector<int> biTreeVec;
	biTree.printAlltoVecPreOrder(biTreeVec);
	std::vector<int> targetVec;
	targetVec.assign({ 1,2,4,5,6,3 });
	CHECK_THAT(biTreeVec, Equals(targetVec));
}

TEST_CASE("testing for member functions of BiTree, isCompleteBinaryTree", "") {
	SqBiTree<int> sqBiTree1(9, 8, { 1,2,3,4,5,6,7,8 }); 
	BiTree<int> biTree1;
	biTree1.createBiTree_from_SqBiTree(sqBiTree1);
	CHECK(true == biTree1.isCompleteBinaryTree());

	SqBiTree<int> sqBiTree2(8, 7, { 1,2,3,-1,-1,5,6 });
	BiTree<int> biTree2;
	biTree2.createBiTree_from_SqBiTree(sqBiTree2);
	CHECK(false == biTree2.isCompleteBinaryTree());
}

TEST_CASE("testing for member functions of BiTree, getNodeCountDegree2", "") {
	SqBiTree<int> sqBiTree1(9, 8, { 1,2,3,4,5,6,7,8 });
	BiTree<int> biTree1;
	biTree1.createBiTree_from_SqBiTree(sqBiTree1);
	CHECK(3 == biTree1.getNodeCountDegree2());
}

TEST_CASE("testing for member functions of BiTree, swap", "") {
	SqBiTree<int> sqBiTree1(9, 8, { 1,2,3,4,5,6,7,8 });
	BiTree<int> biTree1;
	biTree1.createBiTree_from_SqBiTree(sqBiTree1);
	biTree1.swap();
	//biTree1.traverseLevelOrder();//ok
}

TEST_CASE("testing for member functions of BiTree, getKth_PreOrder", "") {
	SqBiTree<int> sqBiTree1(9, 8, { 1,2,3,4,5,6,7,8 });
	BiTree<int> biTree1;
	biTree1.createBiTree_from_SqBiTree(sqBiTree1);

	CHECK(8 == biTree1.getKth_PreOrder(4));
	CHECK(5 == biTree1.getKth_PreOrder(5));
	CHECK(3 == biTree1.getKth_PreOrder(6));
}

TEST_CASE("testing for member functions of BiTree, deleteSubTreeRootedNodeX", "") {
	SECTION("") {
		std::cout << "***testing for member functions of BiTree, deleteSubTreeRootedNodeX***" << std::endl;
	}

	SqBiTree<int> sqBiTree1(9, 8, { 1,2,3,4,5,6,7,8 });
	BiTree<int> biTree1;
	biTree1.createBiTree_from_SqBiTree(sqBiTree1);
	SECTION("") {
		biTree1.deleteSubTreeRootedNodeX(2);
		biTree1.traverseLevelOrder();
	}

	SECTION("") {
		biTree1.deleteSubTreeRootedNodeX(3);
		biTree1.traverseLevelOrder();
	}

	SECTION("") {
		biTree1.deleteSubTreeRootedNodeX(1);
		biTree1.traverseLevelOrder();
	}

	SECTION("") {
		SqBiTree<int> sqBiTree2(9, 8, { 1,2,2,4,5,6,7,8 });
		BiTree<int> biTree2;
		biTree2.createBiTree_from_SqBiTree(sqBiTree2);
		biTree2.deleteSubTreeRootedNodeX(2);
		biTree2.traverseLevelOrder();
	}

	SECTION("") {
		SqBiTree<int> sqBiTree2(9, 8, { 1,2,2,4,5,6,7,8 });
		BiTree<int> biTree2;
		biTree2.createBiTree_from_SqBiTree(sqBiTree2);
		biTree2.deleteSubTreeRootedNodeX_Implement2_with_Ref(2);
		biTree2.traverseLevelOrder();
	}

	SECTION("") {
		std::cout << "***testing for member functions of BiTree, deleteSubTreeRootedNodeX***" << std::endl;
	}
}

TEST_CASE("testing for member functions of BiTree, getClosestCommonAncestor_of_TwoNodes", "") {
	SqBiTree<int> sqBiTree1(9, 8, { 1,2,3,4,5,6,7,8 });
	BiTree<int> biTree1;
	biTree1.createBiTree_from_SqBiTree(sqBiTree1);	
	CHECK(2 == biTree1.getClosestCommonAncestor_of_TwoNodes(5, 8));
	CHECK(1 == biTree1.getClosestCommonAncestor_of_TwoNodes(3, 8));
	CHECK_THROWS([&]() {biTree1.getClosestCommonAncestor_of_TwoNodes(3, 9); }());
	CHECK_THROWS_WITH([&]() {biTree1.getClosestCommonAncestor_of_TwoNodes(3, 9); }(), "无公共结点, p and q does not exist in the same tree.");
}

TEST_CASE("testing for member functions of BiTree, getWidth", "") {
	SECTION("") {
		SqBiTree<int> sqBiTree1(9, 8, { 1,2,3,4,5,6,7,8 });
		BiTree<int> biTree1;
		biTree1.createBiTree_from_SqBiTree(sqBiTree1);
		CHECK(4 == biTree1.getWidth());
	}

	SECTION("") {
		SqBiTree<int> sqBiTree1(9, 6, { 1,2,3,4,5,6 });
		BiTree<int> biTree1;
		biTree1.createBiTree_from_SqBiTree(sqBiTree1);
		CHECK(3 == biTree1.getWidth());
	}
}