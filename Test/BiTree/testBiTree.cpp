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

TEST_CASE("testing for traverseLevelOrder member function of BiTree", "") {
	SqBiTree<int> sqBiTree1(9, 8, { 1,2,3,4,5,6,7,8 });
	BiTree<int> biTree1;
	biTree1.createBiTree_from_SqBiTree(sqBiTree1);
	//biTree1.traverseLevelOrder();

	CHECK(4 == biTree1.getHigh());
	CHECK(4 == biTree1.getHigh_PostOrder_NonRecursive());
}

