#include "SLList.h"

// this tells catch to provide a main()
// only do this in one cpp file
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Sum of integers for a short vector", "[short]") {//"[long]"
    SLList<int> list(6, 4, 2, 4, 3, 9, 4);
    list.insertSort(1);
    list.printAll();
    REQUIRE(list.getData(1) == 9);
}
