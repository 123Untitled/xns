#include "unit_tests.hpp"
#include "iterator_traits.hpp"

/* unit test */
template <>
int UT::unit_tests<"iterator_traits">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_ITERATOR_TRAITS)
int main(void) {
	return UT::unit_tests<"iterator_traits">();
}
#endif


