#include "Queue.h"
#include "catch.hpp"
using namespace Catch::Matchers;

TEST_CASE("testing for basic Operations of Queue", "") {
	Queue<int> queue(6);//do note:牺牲一个存储单元。6 means the dataArr has 6 storage units, but effectively the queue only has 5 ones. 

	int i = 1;
	while (i != 6) {
		queue.push(i);
		++i;
	}

	CHECK(queue.back() == 5);

	CHECK_THROWS([&]() {
		queue.push(6);
		}());

	i = 1;
	std::vector<int> frontVec;
	while (i != 6) {
		frontVec.push_back(queue.front());
		queue.pop();
		++i;
	}
	std::vector<int> targetVec;
	targetVec.assign({ 1,2,3,4,5 });
	CHECK_THAT(targetVec, Equals(frontVec));

	CHECK_THROWS([&] {//queue can be implicitly captured, and the capture mode is specified as reference mode.
		queue.pop();
		}());
}

TEST_CASE("testing for basic Operations of CSLQueue", "") {
	CSLQueue<int> queue;

	int i = 1;
	while (i != 6) {
		queue.push(i);
		++i;
	}

	CHECK(queue.back() == 5);

	i = 1;
	std::vector<int> frontVec;
	while (i != 6) {
		frontVec.push_back(queue.front());
		queue.pop();
		++i;
	}
	std::vector<int> targetVec;
	targetVec.assign({ 1,2,3,4,5 });
	CHECK_THAT(targetVec, Equals(frontVec));

	CHECK_THROWS([&] {//queue can be implicitly captured, and the capture mode is specified as reference mode.
		queue.pop();
		}());
}