#include "Stack.h"
#include "catch.hpp"
using namespace Catch::Matchers;

TEST_CASE("testing for basic Operations of Stack", "") {
	Stack<int> stk(5);

	int i = 1;
	while (i != 6) {
		stk.push(i);
		++i;
	}

	CHECK_THROWS([&]() {
		stk.push(6);
		}());

	i = 1;
	std::vector<int> popVec;
	while (i != 6) {
		popVec.push_back(stk.top());
		stk.pop();
		++i;
	}
	std::vector<int> targetVec;
	targetVec.assign({ 5,4,3,2,1 });
	CHECK_THAT(targetVec, Equals(popVec));

	CHECK_THROWS([&] {//stk can be implicitly captured, and the capture mode is specified as reference mode.
		stk.pop();
		}());
}