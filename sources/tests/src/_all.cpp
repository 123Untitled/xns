#include "input.hpp"
#include "integer_sequence.hpp"
#include "tuple.hpp"
#include "unit_tests.hpp"
#include "exceptions.hpp"
#include "vector.hpp"
#include <__bit/bit_ceil.h>
#include <cstddef>
#include <cstdio>
#include <functional>
#include <iostream>

// launch all tests 🚀
#include <map>
#include <memory>
#include <set>
#include <strings.h>
#include <tuple>
#include <unistd.h>
#include <utility>
#include <vector>
#include <string>



#if defined(XNS_TEST_ALL)
int main(const int ac, const char** av) {

	// start main function
	try { UT::launcher(); }
	// catch memory errors
	catch (const xns::exception& except) {

		// return failure
		return EXIT_FAILURE;
	} // else return success
	return EXIT_SUCCESS;
}
#endif





