#include <iostream>
#include "../ArrayStack.h"
using std::cin;
using std::cout;
using std::endl;

using std::string;


// 1. 피연산자는 그대로 출력한다.
// 2. 연산자는 스택이 비어있으면 자신을 바로 추가한다.
// 3. stack의 top이 자신보다 우선순위가 낮은 연산자를 만날 때까지 pop 하고 자신을 담는다.
// 4. 단, 여는 괄호는 닫는 괄호가 아니면 pop하지 않는다.
// 5. 닫는 괄호가 나오면 여는 괄호가 나올 때까지 꺼내서 출력한다.
// 6. 마지막에 도착하면 스택에서 차례로 꺼내서 출력한다.

auto postfixExpression(ArrayStack<char>& operatorStack, string expression) {
	string result{ };

	for (const auto& oper : expression) {
		// 여는 괄호는 무조건 그대로 push
		switch (oper) {
		case '(':
			operatorStack.push('(');
			break;

			// 닫는 괄호가 오면 여는 괄호가 나올때까지 pop 
		case ')':
			while (!operatorStack.empty() and operatorStack.top() != '(') {
				result.push_back(operatorStack.top());
				operatorStack.pop();
			}
			// 스택에 쌓여있는 ( 제거
			operatorStack.pop();
			break;


		case '*': case '/':
			// stack의 top이 자신보다 우선순위가 낮은 연산자를 만날 때까지 pop 하고 자신을 push
			// * / 의 경우 자신보다 우선순위가 낮은 연산자는 + -
			// 다시 말해 + -이 아닌 경우, 즉 * / 일 때 반복한다.
			while (!operatorStack.empty() and (operatorStack.top() == '*' or operatorStack.top() == '/')) {
				result.push_back(operatorStack.top());
				operatorStack.pop();
			}
			operatorStack.push(oper);
			break;

		case '+': case '-':
			while (!operatorStack.empty() and operatorStack.top() != '(') {
				result.push_back(operatorStack.top());
				operatorStack.pop();
			}
			operatorStack.push(oper);
			break;

		// 피연산자는 그대로 출력
		default:
			result.push_back(oper);

		}
	}

	while (!operatorStack.empty()) {
		result.push_back(operatorStack.top());
		operatorStack.pop();
	}

	return result;
}


auto main() -> int {
	ArrayStack<char> operatorStack{ };
	cout << postfixExpression(operatorStack, "A * B * C") << endl;
	cout << postfixExpression(operatorStack, "((A+(B*C))-(D/E))") << endl;
	cout << postfixExpression(operatorStack, "-A + B - C + D") << endl;
	cout << postfixExpression(operatorStack, "A * -B + C") << endl;
	cout << postfixExpression(operatorStack, "(A + B) * D + E / (F + A * D) + C") << endl;
	cout << postfixExpression(operatorStack, "A && B || C || !(E > F)") << endl;
	cout << postfixExpression(operatorStack, "!(A && !((B < C) || (C > D))) || (C < E)") << endl;
	return 0;
}
