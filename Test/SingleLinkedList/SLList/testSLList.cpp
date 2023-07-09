
#include "SLList.h"

// this tells catch to provide a main()
// only do this in one cpp file
/*
* do note that the following macro generates a file also named main.cpp,
* so a file named main.cpp must not appear in your project.
*/
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("test for SLList<int>", "[short]") {//"[long]"tag
    SLList<int> list(6, 4,2,4,3,9,4);
    list.insertSort(1);
    //list.printAll();
    REQUIRE(list.getData(1) == 9);
    REQUIRE(list.getData(2) == 4);
    REQUIRE(list.getData(3) == 4);
    REQUIRE(list.getData(4) == 4);
    CHECK_FALSE(list.getData(5) == 100);//Ϊ�˲�����failed.
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
        CHECK_THAT(vecOrigin, !Equals(vecLater));//CHECK_THAT�ķ���ʽ����works.
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
    //delete�ͷ���ָ����ָ�Ŀռ䣬�������Ѹ�ָ��ָ��nullptr��ָ�򲻱�
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

/*type parametrized test cases*/
/*
TEMPLATE_TEST_CASE("test for SLList<int> and SLList<double>", "[long]", int, double) {
    SLList<TestType> list(6, 4, 2, 4, 3, 9, 4);
    list.insertSort(1);
    list.printAll();
    REQUIRE(list.getData(1) == 9);
}
*/
