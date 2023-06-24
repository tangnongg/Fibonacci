#include <iostream>
#include <string>

#include "Header/Fibonacci.h"

#include "Header/SqList.h"

int main() {
    SqList<int> sqList02(10, 6, 2,5,3,6,4,9);
    SqList<int> sqList03=sqList02;//execute copy structor
    sqList03.printAll();

    SqList<int> sqList04;
    sqList04=sqList02;//perform copy assignment operator
    sqList04.printAll();

    SqList<int> sqList05(10,6, 4,4,4,2,5,2);
    sqList05.beingNoSameElement(1);
    sqList05.printAll();
}
