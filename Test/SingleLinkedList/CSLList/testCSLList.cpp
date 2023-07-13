
#include "CSLList.h"

#include "catch.hpp"
using namespace Catch::Matchers;

TEST_CASE("testing for CSLList<int>", "") {
    CSLList<int> list1(6, 4,2,4,3,9,4);
    std::vector<int> listVec;
    list1.printAll_to_Vector(listVec);
    std::vector<int> targetVec;
    targetVec.assign({ 4,2,4,3,9,4 });
    CHECK_THAT(targetVec, Equals(listVec));

    
}

TEST_CASE("testing for emerge of CSLList", "") {
    CSLList<int> list1(6, 4, 2, 4, 3, 9, 4);
    CSLList<int> list2(3, 99, 100, 99);
    list1.emerge(list2);

    std::vector<int> list1VecAfterOp;
    list1.printAll_to_Vector(list1VecAfterOp);
    std::vector<int> list2VecAfterOp;
    list2.printAll_to_Vector(list2VecAfterOp);

    std::vector<int> targetVec1;
    targetVec1.assign({ 4,2,4,3,9,4, 99,100,99 });
    CHECK_THAT(targetVec1, Equals(list1VecAfterOp));
    std::vector<int> targetVec2;
    targetVec2.assign({});
    CHECK_THAT(targetVec2, Equals(list2VecAfterOp));

    CHECK(list1.getLength() == 9);
    CHECK(list2.getLength() == 0);
}


TEST_CASE("testing for deleteMin & deleteMinRepeatly of CSLList", "") {
    CSLList<int> list1(6, 4, 2, 4, 3, 9, 4);
    int ret = list1.deleteMin();
    CHECK(ret == 2);
    std::vector<int> list1VecAfterOp;
    list1.printAll_to_Vector(list1VecAfterOp);
    std::vector<int> targetVec1;
    targetVec1.assign({ 4, 4, 3, 9, 4 });
    CHECK_THAT(targetVec1, Equals(list1VecAfterOp));
    CHECK(list1.getLength() == 5);

    CSLList<int> list2(6, 4, 2, 4, 3, 9, 4);
    std::vector<int> targetVec;
    targetVec.assign({2, 3, 4, 4, 4, 9});
    std::vector<int> outputVec;
    list2.deleteMinRepeatly(outputVec);
    CHECK_THAT(targetVec, Equals(outputVec));
    CHECK(list2.getLength() == 0);
}