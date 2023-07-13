
#include "SLList.h"

#include "catch.hpp"

TEST_CASE("test for SLList<int>", "[short]") {//"[long]"tag
    SLList<int> list(6, 4,2,4,3,9,4);
    list.insertSort(1);
    //list.printAll();
    REQUIRE(list.getData(1) == 9);
    REQUIRE(list.getData(2) == 4);
    REQUIRE(list.getData(3) == 4);
    REQUIRE(list.getData(4) == 4);
    CHECK_FALSE(list.getData(5) == 100);//为了不出现failed.
    REQUIRE(list.getData(6) == 2);
}

using namespace Catch::Matchers;
TEST_CASE("test for SLList<int> in a way of using vector matchers", "[tag]") {//"[long]"tag
    SLList<int> list(6, 4, 2, 4, 3, 9, 4);
    std::vector<int> vecOrigin;
    list.printAll_to_Vector(vecOrigin);

    list.insertSort(1);
    //list.printAll();
    std::vector<int> vecLater;
    list.printAll_to_Vector(vecLater);

    SECTION("order matters for equals operation") {
        CHECK_THAT(vecOrigin, !Equals(vecLater));//CHECK_THAT的否定形式：！works.
    }

    SECTION("order does not matter for equals operation") {
        CHECK_THAT(vecOrigin, UnorderedEquals(vecLater));
    }

    SECTION("subvector") {
        std::vector<int> subVec;
        subVec.push_back(9);
        subVec.push_back(4);
        CHECK_THAT(vecOrigin, !Equals(subVec));
        CHECK_THAT(vecOrigin, !UnorderedEquals(subVec));
        CHECK_THAT(vecOrigin, Contains(subVec));
        subVec.push_back(9);
        CHECK_THAT(vecOrigin, Contains(subVec));

        CHECK_THAT(vecOrigin, VectorContains(9));
        CHECK_THAT(vecOrigin, VectorContains(2));
    }
}

TEST_CASE("testing for the member function deleteAllValue_between_a_and_b of SLList<int>", "") {
    SLList<int> list(6, 4, 2, 4, 3, 9, 4);

    list.deleteAllValue_between_a_and_b(3, 4);
    std::vector<int> vecAfterDelete;
    list.printAll_to_Vector(vecAfterDelete);

    std::vector<int> vecTarget;
    vecTarget.assign({ 2,9 });
    CHECK_THAT(vecAfterDelete, Equals(vecTarget)); 
}

TEST_CASE("testing for the member function commonNode of SLList<int>", "") {
    SLList<int> list(6, 4, 2, 4, 3, 9, 4);
    SLList<int> emergedList(3, 7, 7, 70);
    emergedList.emerge(list);
    CHECK(list.getHead()->getNext() == list.commonNode(emergedList));
    CHECK(list.getHead()->getNext() == emergedList.commonNode(list)); 
}

TEST_CASE("testing for the member function print_and_Realease of SLList<int>", "") {
    SLList<int> list(6, 4, 2, 4, 3, 9, 4);
    list.print_and_Realease();
    CHECK(list.getLength() == 0);
    //delete释放了指针所指的空间，不会随后把该指针指向nullptr，指向不变
    //CHECK(list.getHead()->getNext() == nullptr);
    //list.printAll();
}

TEST_CASE("testing for the member function divide_into_Two of SLList<int>", "") {
    SLList<int> list(6, 1,2,3,4,5,6);
    SLList<int> retL;
    list.divide_into_Two(retL);

    std::vector<int> retVec;
    retL.printAll_to_Vector(retVec);
    std::vector<int> dividedVec;
    list.printAll_to_Vector(dividedVec);

    std::vector<int> retVecTarget;
    retVecTarget.assign({ 2,4,6 });
    std::vector<int> devidedVecTarget;
    devidedVecTarget.assign({ 1,3,5 });

    CHECK_THAT(retVec, Equals(retVecTarget));
    CHECK_THAT(dividedVec, Equals(devidedVecTarget));
}

TEST_CASE("testing for the member function divide_into_Two_2 of SLList<int>", "") {
    SLList<int> list(6, 1, 2, 3, 4, 5, 6);
    SLList<int> retL;
    list.divide_into_Two_2(retL);

    std::vector<int> retVec;
    retL.printAll_to_Vector(retVec);
    std::vector<int> dividedVec;
    list.printAll_to_Vector(dividedVec);

    std::vector<int> retVecTarget;
    retVecTarget.assign({ 6,4,2 });
    std::vector<int> devidedVecTarget;
    devidedVecTarget.assign({ 1,3,5 });

    CHECK_THAT(retVec, Equals(retVecTarget));
    CHECK_THAT(dividedVec, Equals(devidedVecTarget));
}

TEST_CASE("testing for the member function beingNoSameElement of SLList<int>", "") {
    SLList<int> list(6, 1, 2, 2, 4, 4, 4);
    list.beingNoSameElement();
    std::vector<int> listVecAfterOp;
    list.printAll_to_Vector(listVecAfterOp);

    std::vector<int> targetVec;
    targetVec.assign({ 1, 2, 4 });

    CHECK_THAT(listVecAfterOp, Equals(targetVec));
}

TEST_CASE("testing for the member function emergetoNewList of SLList<int>", "") {
    SLList<int> list(6, 1, 2, 3, 4, 5, 6);
    SLList<int> list2(3, 2, 3, 7);
    list.emergetoNewList(list2);
    
    std::vector<int> listVecAfterOp;
    list.printAll_to_Vector(listVecAfterOp);
    std::vector<int> targetVec;
    targetVec.assign({ 7,6,5,4,3,3,2,2,1 });

    CHECK_THAT(listVecAfterOp, Equals(targetVec));
}

TEST_CASE("testing for the member function generateCommonVlaueList of SLList<int>", "") {
    SLList<int> list(6, 1, 2, 3, 4, 5, 6);
    SLList<int> list2(3, 2,3,7);
    SLList<int> generatedList;
    list.generateCommonVlaueList(list2, generatedList);

    std::vector<int> generatedVec;
    generatedList.printAll_to_Vector(generatedVec);
    std::vector<int> targetVec;
    targetVec.assign({ 2, 3 });

    CHECK_THAT(generatedVec, Equals(targetVec));
}

TEST_CASE("testing for the member function generateCommonVlaueList overload of SLList<int>", "") {
    SLList<int> list(6, 1, 2, 3, 4, 5, 6);
    SLList<int> list2(3, 2, 3, 7);
    list.generateCommonVlaueList(list2);

    std::vector<int> listVecAfterOp;
    list.printAll_to_Vector(listVecAfterOp);
    std::vector<int> targetVec;
    targetVec.assign({ 3, 2 });

    CHECK_THAT(listVecAfterOp, Equals(targetVec));
    CHECK(listVecAfterOp.size()==targetVec.size());
}

TEST_CASE("testing for the member function modeMatch of SLList<int>", "") {
    SLList<char> list(6, 'a', 'a', 'd', 'b', 'c', 'a');
    SLList<char> modeList(2, 'b', 'c');
    
    CHECK(list.modeMatch(modeList)==true);
}


/*type parametrized test cases*/
/*
TEMPLATE_TEST_CASE("test for SLList<int> and SLList<double>", "[long]", int, double) {
    SLList<TestType> list(6, 4, 2, 4, 3, 9, 4);
    list.insertSort(1);
    list.printAll();
    REQUIRE(list.getData(1) == 9);
}
*/
