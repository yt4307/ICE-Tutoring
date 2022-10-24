#include <iostream>
#include <vector>
#include "../ArrayStack.h"
using std::cin;
using std::cout;
using std::endl;

using std::vector;

// https://pang2h.tistory.com/242 ����

auto stockSpan(ArrayStack<int>& span, int& graphSize, vector<int>& graph, vector<int>& output) {
	// �� ó�� �׷����� �Ǵ��� �ʿ䰡 ������ output[0]���� 0�� ����
	// ���� 0�� �ε���, �� �� ó�� ���� �׷��� ���� ������ �ִ��̹Ƿ� ���ÿ� �׾��ش�.
	output[0] = 1;
	span.push(0);

	for (int i{ 1 }; i < graphSize; ++i) {
		while (!span.empty() and graph[span.top()] <= graph[i])
			span.pop();

		if (span.empty())
			output[i] = i + 1;
		else
			output[i] = i - span.top();

		span.push(i);
	}

	for (int i{ }; i < graphSize; ++i)
		cout << graph[i] << ' ' << output[i] << endl;
}

auto main() -> int {
	ArrayStack<int> span{ };

	int graphSize{ }; cin >> graphSize;

	vector<int> graph(graphSize);
	for (int i{ }; i < graphSize; ++i)
		cin >> graph[i];

	vector<int> output(graphSize);

	stockSpan(span, graphSize, graph, output);

	return 0;
}
