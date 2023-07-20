#include "catch.hpp"
#include "SqBiTree.h"

TEST_CASE("", "") {
	std::cout << "***testing for basic operations of SqBiTree***" << std::endl;

	SqBiTree<int> biTree(5, 5, { 1,2,3,4,5 });
	biTree.printAll();

	SqBiTree<int> biTree2(3, 3, { 1,2,3});
	biTree2.printAll_in_Tree();

	SqBiTree<int> biTree3(7, 7, { 1,2,3,4,5,6,7 });
	biTree3.printAll_in_Tree();

	SqBiTree<int> biTree4(15, 15, { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
	//SqBiTree<int> biTree4(15, 15, { 1,2,3,4,5,6,7,8,9,1,1,1,1,1,1 });
	biTree4.printAll_in_Tree();
	CHECK(biTree4.getHigh_of_Node(1) == 1);
	CHECK(biTree4.getHigh_of_Node(2) == 2);
	CHECK(biTree4.getHigh_of_Node(3) == 2);
	CHECK(biTree4.getHigh_of_Node(4) == 3);
	CHECK(biTree4.getHigh_of_Node(15) == 4);
	CHECK(biTree4.getHigh_of_Node(16) == -1);
	

	CHECK(biTree4.getClosestCommonAncestor_of_TwoNodes(14, 15) == 7);
	CHECK(biTree4.getClosestCommonAncestor_of_TwoNodes(12, 15) == 3);
	CHECK(biTree4.getClosestCommonAncestor_of_TwoNodes(4, 3) == 1);
	CHECK(biTree4.getClosestCommonAncestor_of_TwoNodes(2, 3) == 1);
	CHECK(biTree4.getClosestCommonAncestor_of_TwoNodes(1, 1) == 1);
}