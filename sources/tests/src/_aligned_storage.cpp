#include "unit_tests.hpp"
#include "aligned_storage.hpp"

#define SIZEOF_ALIGNOF(T) std::cout<< sizeof(T) << '/' << alignof(T) << std::endl


/* unit test */
template <>
int UT::unit_tests<"aligned_storage">(void) {


	xns::aligned_storage<sizeof(int), alignof(int)> storage;

	char& ref = xns::ref<char>(storage);
	int* ptr = xns::ptr<int>(storage);


	return false;
}

#if defined(XNS_TEST_ALIGNED_STORAGE)
int main(void) {
	return UT::unit_tests<"aligned_storage">();
}
#endif

