#include "StackApplications.h"
#include "Stack.h"
#include <string>
#include <cctype>//check the type of a character, i.g.isdigit().
#include <cstdlib>//atoi()

/************************************
* 写成C language的函数形式，面向过程
**************************************/

/***************************************************
*	括号匹配（栈的应用）（top最急迫需要被匹配左括号）
* legal   seq:()[],(()),[[]],[([])]
* illegal seq:[),[)],[[[],[]]]
***************************************************/
bool MatchBracket(const std::string& seq) {
	Stack<char> stk(100);//note: 未实现动态增长机制，不同于std::stack
	for (const auto &elem : seq) {
		//识别括号[]()
		if (elem == '(' || elem == '[')
			stk.push(elem);
		else if (elem == ')') {
			if (stk.empty())//illegal
				return false;
			else if (stk.top() == '(')//legal
				stk.pop();
			else//top is '[', illegal
				return false;
		}
		else if (elem == ']') {
			if (stk.empty())
				return false;
			else if (stk.top() == '[')
				stk.pop();
			else
				return false;
		}
		//非[]()，啥也不做
	}
	if (!stk.empty())
		return false;
	else
		return true;
}


/*******************************************
* 中缀表达式-->>后缀表达式
*（算法过程，可以观察到栈中内容的变化）
* note:输入字符串，要求输入正确。暂时只支持一位数字的操作数。
* 待扫描的中缀表达式序列  扫描项  符号栈  后缀
*******************************************/
void convertExpressMid_to_Post(const std::string& midSeq, std::string& postSeq) {
	Stack<char> stk(100);
	for(const auto &elem:midSeq) {
		if (isdigit(elem))//暂时只支持一位的数字（0~9），支持多位数字需要检查扫描项的下一位是否也为数字
			postSeq.push_back(elem);
		else if (elem == '(')
			stk.push(elem);
		else if (elem == ')') {
			while (stk.top() != '(') {
				postSeq.push_back(stk.top());
				stk.pop();
			}
			stk.pop();
		}
		else {//elem is an operator
			//assign priorities for the two.
			int topPriority = 0;
			int elemPriority = 0;
			if (!stk.empty()) {
				if (stk.top() == '+' || stk.top() == '-')
					topPriority = 1;
				else//* or /
					topPriority = 2;
			}
			if (elem == '+' || elem == '-')
				elemPriority = 1;
			else
				elemPriority = 2;

			while (!stk.empty() && stk.top() != '(' && topPriority >= elemPriority) {//“>=的”出栈
				postSeq.push_back(stk.top());
				stk.pop();
			}
			stk.push(elem);
		}
	}
	while (!stk.empty()) {
		postSeq.push_back(stk.top());
		stk.pop();
	}
}


/*******************************************
*  后缀表达式-->>计算结果
*（算法过程，可以观察到栈中内容的变化）
* note:输入字符串，要求输入正确。暂时只支持一位数字的操作数。
* 待扫描的后缀表达式序列  扫描项  操作数栈
*******************************************/
int caculatePostfixExpression(const std::string& postSeq) {
	Stack<int> stk(100);
	for (const auto& elem : postSeq) {
		if (isdigit(elem)) {
			char temp = elem;
			stk.push(atoi(&temp));
		}
		else {
			int firstPop = stk.top();
			stk.pop();
			int laterPop = stk.top();
			stk.pop();
			if(elem=='+')
				stk.push(laterPop + firstPop);
			else if (elem == '-')
				stk.push(laterPop - firstPop);
			else if (elem == '*')
				stk.push(laterPop * firstPop);
			else
				stk.push(laterPop / firstPop);
		}
	}
	return stk.top();
}