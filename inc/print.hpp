#ifndef PRINT_HEADER
#define PRINT_HEADER

// this header implements a printf-like function but with a few differences:
// 1. string format is a compile-time expression
// 2. it is type-safe
// 3. it is constexpr

#include "string.hpp"


namespace xns {

	template <class... A>
	void printf(const char* format, A... args) {

	}


}



#endif
