#ifndef TYPES_HEADER

	#define TYPES_HEADER

	// preprocessor check operating system
	#if defined(__APPLE__) && defined(__MACH__)

		//#include <MacTypes.h>

	#endif

	//#elif defined(__linux__)

		#include <cstdint>
		#include <cstddef>

		using Nullptr = decltype(nullptr);

		using SInt = int;
		using UInt = unsigned int;
		using Char = char;
		using Char8 = char8_t;

		using SInt8 = int8_t;
		using UInt8 = uint8_t;

		using Char16 = char16_t;
		using SInt16 = int16_t;
		using UInt16 = uint16_t;

		using Char32 = char32_t;
		using SInt32 = int32_t;
		using UInt32 = uint32_t;

		using SInt64 = int64_t;
		using UInt64 = uint64_t;

		using SIntmax = intmax_t;
		using UIntmax = uintmax_t;

		using Double = double;
		using Float = float;

		using Size = size_t;


#endif


