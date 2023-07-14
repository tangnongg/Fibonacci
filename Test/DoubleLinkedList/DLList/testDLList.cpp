
#include "catch.hpp"
using namespace Catch::Matchers;
#include "DLList.h"

TEST_CASE("testing for basic operations of DLList<int>", "") {
	DLList<int> list(4, 3, 4, 5, 2);
	std::vector<int> listVec;
	list.printAll_to_Vector(listVec);
	std::vector<int> targetVec;
	targetVec.assign({ 3, 4, 5, 2 });
	CHECK_THAT(listVec, Equals(targetVec));
	CHECK(list.getLength() == 4);
}

