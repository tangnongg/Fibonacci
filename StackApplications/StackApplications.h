#pragma once

#include <string>

bool MatchBracket(const std::string& seq);
void convertExpressMid_to_Post(const std::string& midSeq, std::string &postSeq);
int caculatePostfixExpression(const std::string& postSeq);
