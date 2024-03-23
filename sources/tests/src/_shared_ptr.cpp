#include "xns/memory/shared_ptr.hpp"

#include <iostream>


/* unit test */
auto unit_tests_shared_ptr(void) -> int {


	xns::shared_ptr<int> a;
	xns::shared_ptr<int> b;

	{
		xns::shared_ptr<int> c = xns::make_shared<int>(5);
		b = c;
		a = b;
	}



	return 0;
}

#if defined(XNS_TEST_SHARED_PTR)
int main(void) {
	return unit_tests_shared_ptr();
}
#endif


