#include "unit_tests.hpp"
#include "stack.hpp"
#include "time.hpp"

/* unit test */
template <>
int UT::unit_tests<"stack">(void) {
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


	return 0;
}

#if defined(XNS_TEST_STACK)
int main(void) {
	return UT::unit_tests<"stack">();
}
#endif

