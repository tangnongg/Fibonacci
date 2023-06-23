#include <iostream>
#include <string>

#include "Header/Fibonacci.h"

#include "Header/SqList.h"

int main() {
    Fibonacci fi;
    std::cout << fi.fun(7)<<" "<<fi.recursiveFun(6)<<std::endl;


    SqList<int> sqList(10);
    try{
        sqList.customDelete();
    }
    catch(std::string str){
        std::cout<<"err: "<<str<<std::endl;
    }

    SqList<int> sqList01(10, 6, 3, 5, 6, 2, 9,33);
    sqList01.printAll();
    sqList01.reverse();
    sqList01.printAll();

    sqList01.deleteAllValueX(3);
    sqList01.printAll();

    sqList01.bubbleSort(0);
    sqList01.printAll();

}

