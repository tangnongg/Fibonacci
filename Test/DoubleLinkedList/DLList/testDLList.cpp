
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

TEST_CASE("testing for _freq_ operations of DLList<int>", "") {
	std::cout << "***testing for _freq_ operations of DLList<int>***" << std::endl;
	DLList<int> list(4, 1, 2, 3, 4);
	list.assignFreq(4, 4, 3, 2, 0);
	list.printAll_and_Freq();
	list.locate(4);
	list.printAll_and_Freq();
	list.locate(4);
	list.printAll_and_Freq();
	std::cout << "***testing for _freq_ operations of DLList<int>***" << std::endl;
}
