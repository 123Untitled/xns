#include "unit_tests.hpp"
#include "xns/memory/memory.hpp"
#include "xns/memory/allocator.hpp"

#include <vector>
#include "xns/containers/tuple.hpp"
#include "xns/time/time.hpp"

template <decltype(sizeof(0)) N>
class test {
	char c[N];
};// __attribute__((packed));

/* unit test */

auto unit_tests_memory(void) -> int {

	using type = test<10>;

	std::cout << "size of : " << sizeof(type) << std::endl;

	auto pad = xns::memory::padding<type>();

	std::cout << "padding : " << pad << std::endl;

	std::cout << "alignof : " << alignof(type) << std::endl;

	std::cout << "total : " << sizeof(type) + pad << std::endl;


	return 0;
}

#if defined(XNS_TEST_MEMORY)
int main(void) {
	return unit_tests_memory();
}
#endif

