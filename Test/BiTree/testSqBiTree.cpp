#include "catch.hpp"
#include "SqBiTree.h"
#include <string>

//using Catch::Matchers::Equals;
using namespace Catch::Matchers;

TEST_CASE("testing for basic operations of SqBiTree", "") {
	std::cout << "***testing for basic operations of SqBiTree***" << std::endl;
	SqBiTree<int> biTree(6, 5, { 1,2,3,4,5 });
	//biTree.printAll();	

	CHECK_THROWS([] {
		SqBiTree<int> biTreeException(5, 5, { 1,2,3,4,5 });
		}());//note:lamda exppression must have the parenthesis in catch 

	REQUIRE_THROWS_WITH([] {
		SqBiTree<int> biTreeException(5, 5, { 1,2,3,4,5 });
		}(), 
		Equals("wrong size or count!"));

	SqBiTree<int> biTree2(4, 3, { 1,2,3});
	biTree2.printAll_in_Tree();

	SqBiTree<int> biTree3(8, 7, { 1,2,3,4,5,6,7 });
	biTree3.printAll_in_Tree();

	SqBiTree<int> biTree4(16, 15, { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
	//SqBiTree<int> biTree4(16, 15, { 1,2,3,4,5,6,7,8,9,1,1,1,1,1,1 });
	biTree4.printAll_in_Tree();
	std::cout << "***testing for basic operations of SqBiTree***" << std::endl;

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

	//SqBiTree<int> biTree5(8, 7, { 2,1,4,-1,-1,0,5 });
	//CHECK(false == biTree5.isBST());
	//SqBiTree<int> biTree6(8,7, { 2,1,4,-1,-1,3,5});
	//CHECK(true == biTree6.isBST());

	SqBiTree<int> biTree5(8, 7, { 2,1,4,-1,-1,0,5 });
	CHECK(false == biTree5.isBST());
	SqBiTree<int> biTree6(8, 7, { 2,1,4,-1,-1,3,5 });
	CHECK(true == biTree6.isBST());

}