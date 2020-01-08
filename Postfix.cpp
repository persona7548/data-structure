// 중위표기 ( 1 + 3 ) * 2 / ( 6 - 4 ) ^ 2 를 후위표기로 바꾼뒤 계산하는 함수 구현

#include<iostream>
#include<stack>
#include<string>
#include<math.h>

using namespace std;

class Postfix_Conver_Eval {
	string infix;
	string postfix;

	bool isOperand(char C) { //입력받은게 숫자인지 확인하는 함수
		if (C >= '0' && C <= '9') return true;
		return false;
	}

	bool IsOperator(char C) { //입력받은게 부호인지 확인하는 함수
		if (C == '+' || C == '-' || C == '*' || C == '/' || C == '^')
			return true;
		return false;
	}

	int getOperW(char c) { //부호간의 ISP를 나누는 함수
		int weight = -1;
		switch (c)
		{
		case '+':
		case '-': 
			weight = 1;
			break;
		case '*': 
		case '/': 
			weight = 2;
			break;
		case '^': 
			weight = 3;
			break;
		}
		return weight;
	}

	bool LowOrEqualPrecedence(char op1, char op2) { //부호간의 순서를 결정하기 위해 필요한 함수
		int op1W = getOperW(op1);
		int op2W = getOperW(op2);
		if (op1W <= op2W) {
			return true;
		}
		else
			return false;
	}

	bool isOpPara(char c) { //여는괄호인지 확인하는 함수
		if (c == '(' || c == '{' || c == '[')
			return true;
		return false;
	}

	bool isSpaceProvider(char c) { //공백이나 쉼표를 확인하는 함수
		if (c == ' ' || c == ',')
			return true;
		return false;
	}

	bool isClosingParanthesis(char c) { //닫는 괄호인지 확인하는 함수
		if (c == ')' || c == '}' || c == ']')
			return true;
		return false;
	}
	
	bool isMatchingParanthesis(char closing, char opening) {
		if (opening == '{' && closing == '}') return true;
		if (opening == '(' && closing == ')') return true;
		if (opening == '[' && closing == ']') return true;
		return false;
	}

	bool isParanthesisBalanced() {
		stack<char> s;
		for (int i = 0; i<infix.length(); ++i) {
			if (isSpaceProvider(infix[i])) continue;
			else if (isOpPara(infix[i]))
				s.push(infix[i]);
			else if (isClosingParanthesis(infix[i])) {
				if (s.empty() || !isMatchingParanthesis(infix[i], s.top()))
					return false;
				s.pop();
			}
		}
		if (s.empty())
			return true;
		return false;
	}

public:
	Postfix_Conver_Eval(string infix) {
		this->infix = infix;
		postfix = "";
	}


	void convert() { // 중위표기를 후위표기로 바꾸는 함수
		stack<char> s;
		for (int i = 0; i<infix.length(); ++i) {
			if (isSpaceProvider(infix[i])) continue;
			else if (IsOperator(infix[i])) {
				while (!s.empty() && !isOpPara(s.top()) && LowOrEqualPrecedence(infix[i], s.top())) {
					postfix += s.top();
					s.pop();
				}
				s.push(infix[i]);
			}
			else if (isOperand(infix[i]))
				postfix += infix[i];
			else if (isOpPara(infix[i]))
				s.push(infix[i]);
			else if (isClosingParanthesis(infix[i])) {
				while (!isOpPara(s.top())) {
					postfix += s.top();
					s.pop();
				}
				s.pop();
			}
		}
		while (!s.empty()) {
			postfix += s.top();
			s.pop();
		}
		cout << "후위표기 변환 결과 : " << postfix << endl;
	}

	int performOperation(int operand1, int operand2, char operation) { // 부호에 따른 계산결과를 출력하는 함수
		switch (operation) {
		case '+': return operand1 + operand2;
		case '-': return operand1 - operand2;
		case '*': return operand1*operand2;
		case '/':return operand1 / operand2;
		case '^': return (int)pow(operand1 , operand2);
		default: return -1;
		}
	}

	void evaluate() {// 후위표기를 계산하는 함수
			int operand1;
			int operand2;
			stack<int> s;
			for (int i = 0; i < postfix.length(); ++i) {
				if (isOperand(postfix[i])) {
					int operand = 0;
					operand = postfix[i]-48;
					s.push(operand);
				}
				else if (IsOperator(postfix[i])) {
					operand2 = s.top(); s.pop();
					operand1 = s.top(); s.pop();
					int result = performOperation(operand1, operand2, postfix[i]);
					s.push(result);
				}

			}
			cout << "후위표기 연산 결과 : " << s.top() << endl;
	}
};


int main() {
	string infix;
	infix = "(1+3)*2/(6-4)^2";
	cout << "중위표기 식 : " << infix << endl;
	Postfix_Conver_Eval* postfixConverter = new Postfix_Conver_Eval(infix);
	postfixConverter->convert();
	postfixConverter->evaluate();

	return 0;
}