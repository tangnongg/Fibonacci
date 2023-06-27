#include <iostream>
#include <string>

#include "Fibonacci/Fibonacci.h"

#include "SqList/SqList.h"

int main() {
    Fibonacci fi;
    fi.fun(4);
    SqList<int> sqList02(10, 6, 2,5,3,6,4,9);
    SqList<int> sqList03=sqList02;//execute copy structor
    sqList03.printAll();

    SqList<int> sqList04;
    sqList04=sqList02;//perform copy assignment operator
    sqList04.printAll();

    SqList<int> sqList05(6,6, 4,4,4,2,5,2); 
    std::cout << sqList05.getLength() << std::endl;
    sqList05.beingNoSameElement(1);
    sqList05.printAll();

    SqList<int> doubleList(6, 6, 4, 4, 4, 2, 5, 2);
    std::cout << doubleList.getLength() << std::endl;
    doubleList.insertAt_pos(3, 9);
    doubleList.printAll();
}
