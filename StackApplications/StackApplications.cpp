#include "StackApplications.h"
#include "Stack.h"
#include <string>
#include <cctype>//check the type of a character, i.g.isdigit().
#include <cstdlib>//atoi()

/************************************
* д��C language�ĺ�����ʽ���������
**************************************/

/***************************************************
*	����ƥ�䣨ջ��Ӧ�ã���top�����Ҫ��ƥ�������ţ�
* legal   seq:()[],(()),[[]],[([])]
* illegal seq:[),[)],[[[],[]]]
***************************************************/
bool MatchBracket(const std::string& seq) {
	Stack<char> stk(100);//note: δʵ�ֶ�̬�������ƣ���ͬ��std::stack
	for (const auto &elem : seq) {
		//ʶ������[]()
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
		//��[]()��ɶҲ����
	}
	if (!stk.empty())
		return false;
	else
		return true;
}


/*******************************************
* ��׺���ʽ-->>��׺���ʽ
*���㷨���̣����Թ۲쵽ջ�����ݵı仯��
* note:�����ַ�����Ҫ��������ȷ����ʱֻ֧��һλ���ֵĲ�������
* ��ɨ�����׺���ʽ����  ɨ����  ����ջ  ��׺
*******************************************/
void convertExpressMid_to_Post(const std::string& midSeq, std::string& postSeq) {
	Stack<char> stk(100);
	for(const auto &elem:midSeq) {
		if (isdigit(elem))//��ʱֻ֧��һλ�����֣�0~9����֧�ֶ�λ������Ҫ���ɨ�������һλ�Ƿ�ҲΪ����
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

			while (!stk.empty() && stk.top() != '(' && topPriority >= elemPriority) {//��>=�ġ���ջ
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
*  ��׺���ʽ-->>������
*���㷨���̣����Թ۲쵽ջ�����ݵı仯��
* note:�����ַ�����Ҫ��������ȷ����ʱֻ֧��һλ���ֵĲ�������
* ��ɨ��ĺ�׺���ʽ����  ɨ����  ������ջ
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