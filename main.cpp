#include <iostream>
#include <string>

#include "Fibonacci/Fibonacci.h"

#include "SqList/SqList.h"

int main() {

	SqList<int> ls(3,3, -1,0,9);
	//SqList<int> list2(8, 4, -25,-10,10, 11,5,3,4,1);
	//SqList<int> list3(8, 5, 2,9,17,30,41, 3,4,1);
	SqList<int> list2(8, 4,   -25, -10, 10,11);
	SqList<int> list3(8, 5,   2, 9, 17, 30, 41);
	int curTriples[3];
	std::cout << ls.findMinDistance_of_triples(list2, list3, curTriples) << std::endl;
	for (int i = 0; i < 3; ++i)
		std::cout << curTriples[i] << std::endl;
}
