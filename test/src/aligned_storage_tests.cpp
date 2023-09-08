#include "unit_tests.hpp"
#include "aligned_storage.hpp"

#define SIZEOF_ALIGNOF(T) std::cout<< sizeof(T) << '/' << alignof(T) << std::endl


/* unit test */
template <>
bool UT::unit_tests<"aligned_storage">(void) {


	xns::aligned_storage<sizeof(int), alignof(int)> storage;

	char& ref = xns::ref<char>(storage);
	int* ptr = xns::ptr<int>(storage);


	return false;
}

int main(void) {
	return UT::unit_tests<"aligned_storage">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

