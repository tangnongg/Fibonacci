#include "catch.hpp"
#include "BiTree.h"
using namespace Catch::Matchers;

TEST_CASE("testing for basic operations of BiTree", "") {
	SqBiTree<int> biTree2(4, 3, { 1,2,3 });
	
	BiTree<int> biTree;
	biTree.createBiTree_from_SqBiTree(biTree2);

	//biTree.traversePreOrder();
	std::vector<int> biTreeVec;
	biTree.printAlltoVecPreOrder(biTreeVec);
	std::vector<int> targetVec;
	targetVec.assign({ 1,2,3 });
	CHECK_THAT(biTreeVec, Equals(targetVec));
	CHECK(biTree.getCount() == 3);
}