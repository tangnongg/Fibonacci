#include "Stack.h"
#include "StackApplications.h"
#include "catch.hpp"
#include "StackApplications.h"
#include <iostream>
using namespace Catch::Matchers;

TEST_CASE("testing for StackApplications", "") {
	std::string bracketSeq = "[[()";
	CHECK(MatchBracket(bracketSeq) == false);
	bracketSeq = "[)";
	CHECK(MatchBracket(bracketSeq) == false);
	bracketSeq = "[)";
	CHECK(MatchBracket(bracketSeq) == false);
	bracketSeq = "())";
	CHECK(MatchBracket(bracketSeq) == false);
	bracketSeq = "[()][[]()]";
	CHECK(MatchBracket(bracketSeq) == true);


	std::string midSeq = "1/2+(3*4-5*6)/7";
	std::string postSeq;
	convertExpressMid_to_Post(midSeq, postSeq);
	CHECK_THAT(postSeq, Equals("12/34*56*-7/+"));

	int result = caculatePostfixExpression(postSeq);
	CHECK(result==-2);


	midSeq = "1+2-1*((3+4)/5-6)+7";
	postSeq = "";
	convertExpressMid_to_Post(midSeq, postSeq);
	CHECK_THAT(postSeq, Equals("12+134+5/6-*-7+"));

	result = caculatePostfixExpression(postSeq);
	CHECK(result == 15);
}