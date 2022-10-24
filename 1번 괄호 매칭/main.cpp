#include <iostream>
using std::cin;
using std::cout;
using std::endl;

using std::string;

// ��ȣ ��Ī ����
// 1. ���ʰ� �������� ��ȣ�� ������ ���ƾ� �Ѵ�.
// 2. ���� Ÿ���� ��ȣ���� ���� ��ȣ�� ������ ��ȣ���� ���� ���;� �Ѵ�.
// 3. ���� �ٸ� Ÿ���� ���� ��ȣ�� ������ ��ȣ ���� ���θ� �����ϸ� �� �ȴ�.

struct Node {
	char data;
	Node* next;
};

// ��ũ�� ����Ʈ�� �̿��� ���� �� ����
class Stack {
public:
	Stack() : head{ }, tail{ } { }

	auto isEmpty() { return head == nullptr; }

	auto push(char data) {
		// C++ 20 ���� �� �ϳ��� ������ �ʱ�ȭ(Designated Initializer)
		// Ư�� ������ �ʱ�ȭ �ϱ� ���ϴ� ��������� .������� �̷������� ����,
		// �ش� ��������� ���� ���ϴ� ������ �ʱ�ȭ �� �� �ִ�.
		// �������� ���� ����������� �⺻������ �ʱ�ȭ
		Node* node{ new Node{.data{ data } } };

		// ������ ����ִٸ�,
		if (isEmpty())
			// �� node�� tail�� ����Ű�� �ϰ�, �װ� head�� ����Ű�� �Ѵ�. 
			head = tail = node;
		else
			// �׷��� �ʴٸ� �� ��带 tail�� next�� ����Ű�� �ϰ�, �װ� tail�� ����Ű�� �Ѵ�.
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
