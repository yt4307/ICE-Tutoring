#include <iostream>
#include "../ArrayStack.h"
using std::cin;
using std::cout;
using std::endl;

using std::string;


// 1. �ǿ����ڴ� �״�� ����Ѵ�.
// 2. �����ڴ� ������ ��������� �ڽ��� �ٷ� �߰��Ѵ�.
// 3. stack�� top�� �ڽź��� �켱������ ���� �����ڸ� ���� ������ pop �ϰ� �ڽ��� ��´�.
// 4. ��, ���� ��ȣ�� �ݴ� ��ȣ�� �ƴϸ� pop���� �ʴ´�.
// 5. �ݴ� ��ȣ�� ������ ���� ��ȣ�� ���� ������ ������ ����Ѵ�.
// 6. �������� �����ϸ� ���ÿ��� ���ʷ� ������ ����Ѵ�.

auto postfixExpression(ArrayStack<char>& operatorStack, string expression) {
	string result{ };

	for (const auto& oper : expression) {
		// ���� ��ȣ�� ������ �״�� push
		switch (oper) {
		case '(':
			operatorStack.push('(');
			break;

			// �ݴ� ��ȣ�� ���� ���� ��ȣ�� ���ö����� pop 
		case ')':
			while (!operatorStack.empty() and operatorStack.top() != '(') {
				result.push_back(operatorStack.top());
				operatorStack.pop();
			}
			// ���ÿ� �׿��ִ� ( ����
			operatorStack.pop();
			break;


		case '*': case '/':
			// stack�� top�� �ڽź��� �켱������ ���� �����ڸ� ���� ������ pop �ϰ� �ڽ��� push
			// * / �� ��� �ڽź��� �켱������ ���� �����ڴ� + -
			// �ٽ� ���� + -�� �ƴ� ���, �� * / �� �� �ݺ��Ѵ�.
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

		// �ǿ����ڴ� �״�� ���
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
