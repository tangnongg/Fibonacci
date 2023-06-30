#include <iostream>
#include <string>

#include "Fibonacci/Fibonacci.h"

#include "SqList/SqList.h"

int main() {
	SqList<int> list(10,8, 2,4,6,8,10, 3,5,7);
	//list.reverse(3, 3);
	//list.printAll();
	list.swapTwoPart(5, 3);
	//list.cyclicLeftShift(5);
	list.printAll();

	SqList<int> ls(5,5, 5,6,7,8,10);
	int ret = ls.find_x_and_DoSth(8);
	std::cout << ret << std::endl;
	ls.printAll();
}
