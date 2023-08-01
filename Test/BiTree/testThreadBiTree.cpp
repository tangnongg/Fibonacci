#include "catch.hpp"
#include "ThreadBiTree.h"
using namespace Catch::Matchers;

TEST_CASE("testing for traverseLevelOrder member function of ThreadBiTree", "") {
	std::cout << "***traverse_by_InfixThread***" << std::endl;
	SqBiTree<int> sqBiTree(9, 8, { 1,2,3,4,5,6,7,8 });
	ThreadBiTree<int> threadBiTree;
	threadBiTree.createBiTree_from_SqBiTree(sqBiTree);
	//threadBiTree.traverseInOrder();
	//threadBiTree.thread();
	threadBiTree.traverse_by_InfixThread();
	std::cout << "***traverse_by_InfixThread***" << std::endl;
}