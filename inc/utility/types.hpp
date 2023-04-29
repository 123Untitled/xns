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

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- T Y P E S -------------------------------------------------------------

	/* null pointer */
	using Nullptr = decltype(nullptr);

}

/* char types */
using Char    = char;
using SChar   = signed   char;
using UChar   = unsigned char;

/* short types */
using Short   = short;
using SShort  = signed   short;
using UShort  = unsigned short;

/* int types */
using Int     = int;
using SInt    = signed   int;
using UInt    = unsigned int;

/* long types */
using Long    = long;
using SLong   = signed   long;
using ULong   = unsigned long;

/* long long types */
using LLong   = long long;
using SLLong  = signed   long long;
using ULLong  = unsigned long long;

/* float types */
using Float   = float;
using Double  = double;
using LDouble = long double;

/* boolean types */
using Bool    = bool;



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

using SInt8  = Signed<1>;
using UInt8  = Unsigned<1>;

using SInt16 = Signed<2>;
using UInt16 = Unsigned<2>;

using SInt32 = Signed<4>;
using UInt32 = Unsigned<4>;

using SInt64 = Signed<8>;
using UInt64 = Unsigned<8>;


// get number of bytes for current architecture
#define ARCH_BYTES (sizeof(void*))



using SizeT = Unsigned<ARCH_BYTES>;




// compile time get greatest integer type
template <typename T, typename U>
struct GetGreatestIntegerType {
	using Type = Xf::conditional_t<(sizeof(T) > sizeof(U)), T, U>;
};

template <typename T, typename U>
using GetGreatestIntegerType_t = typename GetGreatestIntegerType<T, U>::Type;





using Size = UInt64;

// include for struct winsize
#include <sys/ioctl.h>
// include for declval
#include <utility>

using TSize = decltype(std::declval<struct winsize>().ws_row);

#endif


