#include "xns/utility/apply.hpp"

struct A {
	int a;
	void print(const char* msg, int n) noexcept {
		a = n;
		std::cout << msg << " a = " << a << std::endl;
	}
};

/* unit test */
auto unit_tests_apply(void) noexcept -> int {

	xns::tuple<A, const char*, int> t1(A{}, "hello", 123);

	xns::apply(&A::print, t1);

	return 0;
}

#if defined(XNS_TEST_APPLY)
int main(void) {
	return unit_tests_apply();
}
#endif

