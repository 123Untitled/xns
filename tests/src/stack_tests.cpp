#include "unit_tests.hpp"
#include "stack.hpp"
#include "time.hpp"

/* unit test */
template <>
bool UT::unit_tests<"stack">(void) {
	constexpr int N = 10000000;

	// with old allocator
	// stack -> 125080083


	xns::stack<int> s;

	auto start = xns::time::now();

	for (int i = 0; i < N; ++i) {
		s.push(i);
	}

	while (not s.empty()) {
		std::cout << s.top() << std::endl;
		s.pop();
	}

	auto end = xns::time::now();

	std::cout << "  stack -> " << end - start << std::endl;


	return false;
}

int main(void) {

	UT::unit_tests<"stack">();

	return 0;
}
