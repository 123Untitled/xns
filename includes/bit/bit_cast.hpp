#ifndef XNS_BIT_CAST_HEADER
#define XNS_BIT_CAST_HEADER

#include "types.hpp"
#include "is_integral.hpp"
#include "memcpy.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {



	// -- B I T  C A S T ------------------------------------------------------

	template <class to, class from>
	constexpr to bit_cast(const from& src) { // NEEDS TO CHECK IF TYPES ARE TRIVIALLY COPYABLE (else undefined behaviour !)

		// check types are same size
		static_assert(sizeof(to) == sizeof(from), "): BIT_CAST REQUIRE SAME SIZE TYPES :(");

		// create destination object
		to dst;

		// copy bytes from source to destination
		xns::memcpy(&dst, &src, sizeof(to));

		// return destination object
		return dst;
	}


	// -- B Y T E S W A P -----------------------------------------------------

	template <class T>
	constexpr T byte_swap(const T& src) {

		// check type is integral
		static_assert(xns::is_integral<T>, "): BIT_SWAP REQUIRES INTEGRAL TYPE :(");
		// need to check 'has unique representation' !!!

		// create destination object
		T dst;

		// get size of type
		const xns::size_t size = sizeof(T);

		// cast pointers to byte pointers
		xns::ubyte* dst_ptr = static_cast<xns::ubyte*>(&dst);

		const xns::ubyte* src_ptr = static_cast<const xns::ubyte*>(&src);

		// loop over size
		for (xns::size_t x = 0; x < size; ++x) {
			// copy byte from source to destination
			dst_ptr[x] = src_ptr[size - x - 1];
		}

		// return destination object
		return dst;
	}


	// -- P R I N T  B I T S --------------------------------------------------

	template <class T>
	void print_bits(const T& src) {

		// get size of type
		constexpr xns::size_t size = sizeof(T);

		// cast pointer to byte pointer
		const xns::ubyte* src_ptr = static_cast<const xns::ubyte*>(&src);

		/*
		// loop over size
		for (xns::size_t x = 0; x < size; ++x) {
			// print byte
			std::cout << std::bitset<8>(src_ptr[size - x - 1]) << " ";
		}
		*/

		// print new line
		//std::cout << std::endl;
	}

}

#endif
