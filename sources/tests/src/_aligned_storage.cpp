#include "unit_tests.hpp"
#include "aligned_storage.hpp"

#define SIZEOF_ALIGNOF(T) std::cout<< sizeof(T) << '/' << alignof(T) << std::endl


/* unit test */

auto unit_tests_aligned_storage(void) -> int {


	xns::aligned_storage<sizeof(int), alignof(int)> storage;

	char& ref = xns::ref<char>(storage);
	int* ptr = xns::ptr<int>(storage);


	return false;
}

#if defined(XNS_TEST_ALIGNED_STORAGE)
int main(void) {
	return unit_tests_aligned_storage();
}
#endif

