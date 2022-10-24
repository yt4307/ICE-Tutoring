#include <iostream>
#include <vector>
#include "../ArrayStack.h"
using std::cin;
using std::cout;
using std::endl;

using std::vector;

// https://pang2h.tistory.com/242 참고

auto stockSpan(ArrayStack<int>& span, int& graphSize, vector<int>& graph, vector<int>& output) {
	// 맨 처음 그래프는 판단할 필요가 없으니 output[0]에는 0을 대입
	// 또한 0번 인덱스, 즉 맨 처음 들어온 그래프 값이 현재의 최댓값이므로 스택에 쌓아준다.
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
