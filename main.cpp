#include <iostream>
#include <string>

#include "Fibonacci/Fibonacci.h"

#include "SqList/SqList.h"

int main() {
	SqList<int> list(8,3, 0,5,5);
	SqList<int> list1(8, 5, 3,7,2,3,4);
	int ret = list.middleElement(list1);
	std::cout << ret << std::endl;
}
