#include <iostream>
using std::cin;
using std::cout;
using std::endl;

using std::string;

// 괄호 매칭 조건
// 1. 왼쪽과 오른쪽의 괄호의 개수가 같아야 한다.
// 2. 같은 타입의 괄호에서 왼쪽 괄호는 오른쪽 괄호보다 먼저 나와야 한다.
// 3. 서로 다른 타입의 왼쪽 괄호와 오른쪽 괄호 쌍은 서로를 교차하면 안 된다.

struct Node {
	char data;
	Node* next;
};

// 링크드 리스트를 이용해 구현 한 스택
class Stack {
public:
	Stack() : head{ }, tail{ } { }

	auto isEmpty() { return head == nullptr; }

	auto push(char data) {
		// C++ 20 문법 중 하나인 지정된 초기화(Designated Initializer)
		// 특정 값으로 초기화 하기 원하는 멤버변수를 .멤버변수 이런식으로 적고,
		// 해당 멤버변수만 내가 원하는 값으로 초기화 할 수 있다.
		// 지정하지 않은 멤버변수들은 기본값으로 초기화
		Node* node{ new Node{.data{ data } } };

		// 스택이 비어있다면,
		if (isEmpty())
			// 새 node를 tail이 가리키게 하고, 그걸 head가 가리키게 한다. 
			head = tail = node;
		else
			// 그렇지 않다면 새 노드를 tail의 next가 가리키게 하고, 그걸 tail이 가리키게 한다.
			tail = tail->next = node;
	}

	auto pop() {
		if (isEmpty())
			return '\0';

		auto returnData{ tail->data };

		if (head == tail) {
			delete tail;
			head = tail = nullptr;
		}
		else {
			Node* ptr{ head };
			while (ptr->next != tail)
				ptr = ptr->next;

			ptr->next = nullptr;
			delete tail;
			tail = ptr;
		}
		return returnData;
	}

	auto top() {
		if (isEmpty())
			return '\0';
		return tail->data;
	}

private:
	Node* head;
	Node* tail;
};

auto bracketCheck(Stack& bracketStack, string str) {
	for (const auto& pairBracket : str) {
		switch (pairBracket) {
		case '(': case '{': case '[':
			bracketStack.push(pairBracket);
			break;

		case ')': case '}': case ']':
			if (bracketStack.isEmpty())
				return false;

			char openBracket{ bracketStack.pop() };
			if (openBracket == '(' and pairBracket != ')' or
				openBracket == '{' and pairBracket != '}' or
				openBracket == '[' and pairBracket != ']')
				return false;
			break;
		}
	}

	if (!bracketStack.isEmpty())
		return false;
	return true;
}

auto main() -> int {
	Stack bracket{ };
	cout << std::boolalpha;
	cout << bracketCheck(bracket, "(1+2)((3*4)){([( )])}") << endl;
	cout << bracketCheck(bracket, "((( )((1+2)){([(3+4 )])}") << endl;
	cout << bracketCheck(bracket, ")(( )){([(a+b )])}") << endl;
	cout << bracketCheck(bracket, "({[c/d])}") << endl;

	return 0;
}
