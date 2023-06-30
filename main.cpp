#include <iostream>
#include <string>

#include "Fibonacci/Fibonacci.h"

#include "SqList/SqList.h"

int main() {
	SqList<int> list(5,5, 2,4,6,8,10, 3,5,7);
	SqList<int> list2(4,4, 3, 5, 7,11);

	list.emerge(list2, 1);
	list.printAll();
}
