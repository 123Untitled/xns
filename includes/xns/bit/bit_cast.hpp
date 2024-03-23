/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_BIT_CAST_HEADER
#define XNS_BIT_CAST_HEADER

#include "xns/type_traits/types.hpp"
#include "xns/type_traits/type_categories/is_integral.hpp"
#include "xns/memory/memcpy.hpp"
#include "xns/type_traits/type_properties/is_trivially_copyable.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- B I T  C A S T ------------------------------------------------------

	template <typename __to, typename __from>
	inline constexpr auto bit_cast(const __from& __src) noexcept -> __to {

		// check types are trivially copyable
		static_assert(xns::are_trivially_copyable<__to, __from>,
				"bit_cast: types are not trivially copyable");

		// check types are same size
		static_assert(sizeof(__to) == sizeof(__from),
				"bit_cast: size mismatch");

		// create destination object
		__to __dst;

		// copy bytes from source to destination
		xns::memcpy(&__dst, &__src, sizeof(__to));

		// return destination object
		return __dst;
	}


	// -- B Y T E  S W A P ----------------------------------------------------

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
