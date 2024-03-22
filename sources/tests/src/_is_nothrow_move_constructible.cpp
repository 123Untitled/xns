//#include "unit_tests.hpp"
#include "type_traits/supported_operations/is_nothrow_move_constructible.hpp"

/* unit test */
int unit_tests_is_nothrow_move_constructible(void) {

	constexpr bool b = xns::is_nothrow_move_constructible<int>;

	return 0;
}

#if defined(XNS_TEST_IS_NOTHROW_MOVE_CONSTRUCTIBLE)
int main(void) {
	return unit_tests_is_nothrow_move_constructible();
}
#endif

