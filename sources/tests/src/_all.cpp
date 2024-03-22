#include "unit_tests.hpp"
#include "diagnostics/exceptions.hpp"

// launch all tests 🚀

#if defined(XNS_TEST_ALL)
int main(const int ac, const char** av) {

	// start main function
	try { /*UT::launcher();*/ }
	// catch memory errors
	catch (const xns::exception& except) {

		// return failure
		return EXIT_FAILURE;
	} // else return success
	return EXIT_SUCCESS;
}
#endif





