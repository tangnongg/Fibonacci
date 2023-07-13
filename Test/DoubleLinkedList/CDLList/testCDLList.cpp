//#define CATCH_CONFIG_MAIN //生成的又是main.cpp, 重名
#include "catch.hpp"
using namespace Catch::Matchers;
#include "CDLList.h"

TEST_CASE("testing for CDLList<int> basic operations", "") {
	CDLList<int> list(5, 7, 6, 5, 3, 2);
	std::vector<int> listVec;
	list.printAll_to_Vector(listVec);
	std::vector<int> targetVec;
	targetVec.assign({ 7, 6, 5, 3, 2 });
	CHECK_THAT(targetVec, Equals(listVec));
	REQUIRE(list.getLength() == 5);
}

TEST_CASE("testing for isSymmetrical of CDLList<int>", "") {
	CDLList<int> list(5, 7, 6, 5, 6, 7);
	CDLList<int> list2(6, 7, 6, 5, 4, 6, 7);
	CDLList<int> list3(1, 3);
	CDLList<int> list4;
	CDLList<int> list5(2, 3,4);
	REQUIRE(list.isSymmetrical() == true);
	REQUIRE(list2.isSymmetrical() == false);
	REQUIRE(list3.isSymmetrical() == true);
	REQUIRE(list4.isSymmetrical() == true);
	REQUIRE(list5.isSymmetrical() == false);
}

