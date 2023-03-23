#ifndef TYPES_HEADER
#define TYPES_HEADER

#include "conditional.hpp"
	// preprocessor check operating system
	//#if defined(__APPLE__) && defined(__MACH__)
	//	#include <MacTypes.h>
	//#elif defined(__linux__)
	//	#include <cstdint>
	//	#include <cstddef>
	//#endif


using Nullptr = decltype(nullptr);

using SInt = int;
using UInt = unsigned int;
using Char = char;
using Double = double;
using Float = float;

template <decltype(sizeof(char)) N>
using Unsigned =	Xf::conditional_t<(sizeof(unsigned char)      == N), unsigned char,
					Xf::conditional_t<(sizeof(unsigned short)     == N), unsigned short,
					Xf::conditional_t<(sizeof(unsigned int)       == N), unsigned int,
					Xf::conditional_t<(sizeof(unsigned long)      == N), unsigned long,
					Xf::conditional_t<(sizeof(unsigned long long) == N), unsigned long long,
					void > > > > >;

template <decltype(sizeof(char)) N>
using Signed =		Xf::conditional_t<(sizeof(signed char)        == N), signed char,
					Xf::conditional_t<(sizeof(signed short)       == N), signed short,
					Xf::conditional_t<(sizeof(signed int)         == N), signed int,
					Xf::conditional_t<(sizeof(signed long)        == N), signed long,
					Xf::conditional_t<(sizeof(signed long long)   == N), signed long long,
					void > > > > >;

using UInt8  = Unsigned<1>;
using UInt16 = Unsigned<2>;
using UInt32 = Unsigned<4>;
using UInt64 = Unsigned<8>;

using SInt8  = Signed<1>;
using SInt16 = Signed<2>;
using SInt32 = Signed<4>;
using SInt64 = Signed<8>;

using Size = UInt64;


#endif


