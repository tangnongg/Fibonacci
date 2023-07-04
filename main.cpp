#include <iostream>
#include <string>

#include "Fibonacci/Fibonacci.h"

#include "SqList/SqList.h"

#include "SingleLinkedList/SLList/SLList.h"

int main() {
	SLList<int> list(6, 4,2,4,3,9,4);
	list.insertSort(1);
	list.printAll();

}
