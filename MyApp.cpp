#include <iostream>
#include <string>

#include "Fibonacci/Fibonacci.h"

#include "SqList/SqList.h"

#include "SingleLinkedList/SLList/SLList.h"


int main() {

	int* pa = new int(1);
	int* pb = pa;
	pa = nullptr;
	if (pb == nullptr)
		std::cout << "yes";
	else
		std::cout << "no";

}

