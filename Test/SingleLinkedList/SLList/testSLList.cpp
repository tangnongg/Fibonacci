
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
    list.printAll();
    REQUIRE(list.getData(1) == 9);
    REQUIRE(list.getData(2) == 4);
    REQUIRE(list.getData(3) == 4);
    REQUIRE(list.getData(4) == 4);
    CHECK(list.getData(5) == 100);
    REQUIRE(list.getData(6) == 2);
}

using namespace Catch::Matchers;
TEST_CASE("test for SLList<int> in a way of using vector matchers", "[tag]") {//"[long]"tag
    SLList<int> list(6, 4, 2, 4, 3, 9, 4);
    std::vector<int> vecOrigin;
    list.printAll_to_Vector(vecOrigin);

    list.insertSort(1);
    list.printAll();
    std::vector<int> vecLater;
    list.printAll_to_Vector(vecLater);

    SECTION("order matters for equals operation") {
        CHECK_THAT(vecOrigin, Equals(vecLater));
    }

    SECTION("order does not matter for equals operation") {
        CHECK_THAT(vecOrigin, UnorderedEquals(vecLater));
    }

    SECTION("subvector") {
        std::vector<int> subVec;
        subVec.push_back(9);
        subVec.push_back(4);
        CHECK_THAT(vecOrigin, Equals(subVec));
        CHECK_THAT(vecOrigin, UnorderedEquals(subVec));
        CHECK_THAT(vecOrigin, Contains(subVec));
        subVec.push_back(9);
        CHECK_THAT(vecOrigin, Contains(subVec));

        CHECK_THAT(vecOrigin, VectorContains(9));
        CHECK_THAT(vecOrigin, VectorContains(2));
    }
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
