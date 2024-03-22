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

#ifndef XNS_TYPES_HEADER
#define XNS_TYPES_HEADER

#include "type_traits/type_operations/declval.hpp"
#include "type_traits/type_transformations/conditional.hpp"
#include "type_traits/type_properties/is_signed.hpp"
#include "type_traits/other/always_false.hpp"
#include "config/macros.hpp"

// include for struct winsize
#include <sys/ioctl.h>



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {




	/* get max sizeof of parameter pack */
	template <typename... A>
	consteval auto sizeof_max(void) -> decltype(sizeof(0)) {
		decltype(sizeof(0)) size = 0;
		((size = (sizeof(A) > size ? sizeof(A) : size)), ...);
		return size;
	}


	/* get max alignof of parameter pack */
	template <typename... A>
	consteval auto alignof_max(void) -> decltype(sizeof(0)) {
		decltype(sizeof(0)) align = 0;
		((align = (alignof(A) > align ? alignof(A) : align)), ...);
		return align;
	}




	// -- C O N S T A N T S ---------------------------------------------------

	// assume unsigned char is 1 byte
	static_assert(sizeof(unsigned char) == 1, "Assumption failed: sizeof(unsigned char) != 1");

	namespace impl {

		/* get the number of bits in a byte */
		consteval auto bits_per_byte(void) noexcept -> decltype(sizeof(0)) {
			decltype(sizeof(0)) count{0};
			for (auto byte{static_cast<unsigned char>(1)}; byte != 0; byte <<= 1)
				++count;
			return count;
		}
	}

	enum : decltype(sizeof(0)) {
		// number of bits in a byte
		bits_per_byte = xns::impl::bits_per_byte(),
		// number of bytes in an address
		bytes_per_address = sizeof(void*),
	};



	// -- T Y P E S -------------------------------------------------------------

	/* terminal size type */
	using term_size = decltype(xns::declval<struct winsize>().ws_row);

	/* null pointer type */
	using null = decltype(nullptr);

	/* void type */
//	template <class...>
//	using void_t = void;





	// -- integer selector ----------------------------------------------------

	template <decltype(sizeof(0)) bytes>
	struct integer_selector final {

		private:

			// -- private types -----------------------------------------------

			/* size type */
			using _size = decltype(bytes);


			// -- private structs ---------------------------------------------

			/* compile time error */
			template <typename T>
			struct compile_time_error {
				static_assert(xns::always_false<T>,
						"This machine does not support this integer type.");
			};

			/* implementation */
			template <typename...>
			struct impl;

			/* parameter pack specialization */
			template <typename T, typename... Tp>
			struct impl<T, Tp...> {
				using type = xns::conditional<sizeof(T) != bytes,
											typename impl<Tp...>::type,
											T>;
			};

			/* end of recursion specialization */
			template <typename T>
			struct impl<T> {
				using type = xns::conditional<sizeof(T) != bytes,
											compile_time_error<T>,
											T>;
			};



		public:

			// -- public types ------------------------------------------------

			using _signed   = typename impl<signed char,
											signed short,
											signed int,
											signed long,
											signed long long>::type;

			using _unsigned = typename impl<unsigned char,
											unsigned short,
											unsigned int,
											unsigned long,
											unsigned long long>::type;

	};


	/* signed integer types */
	template <decltype(sizeof(0)) N>
	using _signed = typename xns::integer_selector<N>::_signed;

	/* unsigned integer types */
	template <decltype(sizeof(0)) N>
	using _unsigned = typename xns::integer_selector<N>::_unsigned;


	/* arch address types */
	using addr_t  = xns::_unsigned<xns::bytes_per_address>;

	/* uintptr types */
	using uptr_t  = xns::_unsigned<xns::bytes_per_address>;

	/* pointer types */
	using ptr_t   = xns::_unsigned<xns::bytes_per_address>;


	/* byte types */
	using sbyte   = xns::_signed<1>;
	using ubyte   = xns::_unsigned<1>;

	/* lowest integer type */
	using s8      = xns::_signed<1>;
	using u8      = xns::_unsigned<1>;

	/* medium integer type */
	using s16     = xns::_signed<2>;
	using u16     = xns::_unsigned<2>;

	/* normal integer type */
	using s32     = xns::_signed<4>;
	using u32     = xns::_unsigned<4>;

	/* highest integer type */
	using s64     = xns::_signed<8>;
	using u64     = xns::_unsigned<8>;


	/* maximum unsigned integer type */
	using size_t = xns::_unsigned<xns::bytes_per_address>;

	/* maximum signed integer type */
	using ssize_t = xns::_signed<xns::bytes_per_address>;


	/* maximum unsigned integer type */
	using umax = xns::_unsigned<xns::bytes_per_address>;

	/* maximum signed integer type */
	using smax = xns::_signed<xns::bytes_per_address>;


	/* floating point types */

	/* lowest floating point type */
	using f32 = float;

	/* highest floating point type */
	using f64 = double;


}


#endif


