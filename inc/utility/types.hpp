#ifndef TYPES_HEADER
#define TYPES_HEADER

#include "conditional.hpp"

// include for struct winsize
#include <sys/ioctl.h>
// include for declval
#include <utility>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- T Y P E S -------------------------------------------------------------

	/* terminal size type */
	using term_size = decltype(std::declval<struct winsize>().ws_row);

	/* null pointer type */
	using null = decltype(nullptr);

	/* void type */
//	template <class...>
//	using void_t = void;


	/* architecture bytes */
	#define ARCH_BYTES (sizeof(void*))


	/* unsigned integer types */
	template <decltype(sizeof(char)) N>
	using unsign =  xns::conditional<(sizeof(unsigned char)      == N), unsigned char,
					xns::conditional<(sizeof(unsigned short)     == N), unsigned short,
					xns::conditional<(sizeof(unsigned int)       == N), unsigned int,
					xns::conditional<(sizeof(unsigned long)      == N), unsigned long,
					xns::conditional<(sizeof(unsigned long long) == N), unsigned long long,
					void > > > > >;

	/* signed integer types */
	template <decltype(sizeof(char)) N>
	using sign =    xns::conditional<(sizeof(signed char)        == N), signed char,
					xns::conditional<(sizeof(signed short)       == N), signed short,
					xns::conditional<(sizeof(signed int)         == N), signed int,
					xns::conditional<(sizeof(signed long)        == N), signed long,
					xns::conditional<(sizeof(signed long long)   == N), signed long long,
					void > > > > >;


	/* byte types */
	using sbyte   = sign<1>;
	using ubyte   = unsign<1>;

	/* lowest integer type */
	using s8      = sign<1>;
	using u8      = unsign<1>;

	/* medium integer type */
	using s16     = sign<2>;
	using u16     = unsign<2>;

	/* normal integer type */
	using s32     = sign<4>;
	using u32     = unsign<4>;

	/* highest integer type */
	using s64     = sign<8>;
	using u64     = unsign<8>;


	/* maximum unsigned integer type */
	using size_t = unsign<ARCH_BYTES>;

	/* maximum signed integer type */
	using ssize_t = sign<ARCH_BYTES>;

}


#endif


