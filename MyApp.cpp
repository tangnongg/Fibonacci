#include <iostream>
#include <string>
#include <stack>

#include "Fibonacci/Fibonacci.h"
#include "SqList/SqList.h"
#include "SingleLinkedList/SLList/SLList.h"

#include "StackApplications.h"


int main() {
	std::string bracketSeq = "[[()";
	if(MatchBracket(bracketSeq))
		std::cout<<"y" << std::endl;
	else
		std::cout << "n" << std::endl;

	std::string midSeq = "1/2+(3*4-5*6)/7";
	std::string postSeq;
	convertExpressMid_to_Post(midSeq, postSeq);
	std::cout << postSeq << std::endl;

	int result = caculatePostfixExpression(postSeq);
	std::cout << result << std::endl;


	midSeq = "1+2-1*((3+4)/5-6)+7";
	postSeq = "";
	convertExpressMid_to_Post(midSeq, postSeq);
	std::cout << postSeq << std::endl;

	result = caculatePostfixExpression(postSeq);
	std::cout << result << std::endl;
}

