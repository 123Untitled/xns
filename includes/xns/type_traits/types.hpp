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

#include "xns/type_traits/type_operations/declval.hpp"
#include "xns/type_traits/type_transformations/conditional.hpp"
#include "xns/type_traits/type_properties/is_signed.hpp"
#include "xns/type_traits/other/always_false.hpp"
#include "xns/config/macros.hpp"
#include "xns/config/config.hpp"




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
	static_assert(sizeof(unsigned char) == 1, "assumption failed: sizeof(unsigned char) != 1");

	namespace __impl {

		/* get the number of bits in a byte */
		consteval auto bits_per_byte(void) noexcept -> decltype(sizeof(0)) {
			decltype(sizeof(0)) __count{0};
			for (auto __byte{static_cast<unsigned char>(1)}; __byte != 0; __byte <<= 1)
				++__count;
			return __count;
		}
	}

	enum : decltype(sizeof(0)) {
		// number of bits in a byte
		bits_per_byte = xns::__impl::bits_per_byte(),
		// number of bytes in an address
		bytes_per_address = sizeof(void*),
	};



	// -- T Y P E S -------------------------------------------------------------

	/* null pointer type */
	using null = decltype(nullptr);

	/* void type */
//	template <class...>
//	using void_t = void;





	// -- I N T E G E R  S E L E C T O R --------------------------------------

	template <decltype(sizeof(0)) __bits>
	class integer_selector final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::integer_selector<__bits>;

			/* size type */
			using size_type = decltype(__bits);


		private:

			// -- private structs ---------------------------------------------

			/* error */
			template <typename __type>
			struct __error final {
				static_assert(xns::always_false<__type>,
						"this machine does not support this integer type.");
			};

			/* implementation */
			template <typename...>
			struct ___;

			/* parameter pack specialization */
			template <typename __type, typename... __types> requires (sizeof...(__types) > 0)
			struct ___<__type, __types...> {
				using __result = xns::conditional<sizeof(__type) * xns::bits_per_byte != __bits,
												  typename ___<__types...>::__result,
												  __type>;
			};

			/* end of recursion specialization */
			template <typename __type>
			struct ___<__type> {
				using __result = xns::conditional<sizeof(__type) * xns::bits_per_byte != __bits,
												  __error<__type>,
												  __type>;
			};


		public:

			// -- public types ------------------------------------------------

			/* signed type */
			using signed_type =
				typename ___<signed char, signed short,
							 signed int,  signed long,
							 signed long long
							 #ifdef XNS_128BIT_INTEGERS
						   , __int128
							 #endif
							 >::__result;

			/* unsigned type */
			using unsigned_type =
				typename ___<unsigned char, unsigned short,
							 unsigned int,  unsigned long,
							 unsigned long long
							 #ifdef XNS_128BIT_INTEGERS
						   , unsigned __int128
							 #endif
							 >::__result;

	}; // class integer_selector




	template <decltype(sizeof(0)) __bits, typename... __params>
	class type_selector final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::type_selector<__bits, __params...>;


		private:

			// -- private types -----------------------------------------------

			/* size type */
			using __size = decltype(__bits);


			// -- private structs -----------------------------------------

			/* error */
			template <typename __type>
			struct __error final {
				static_assert(xns::always_false<__type>,
						"no type with the specified size exists.");
			};

			/* implementation */
			template <typename...>
			struct ___;

			/* parameter pack specialization */
			template <typename __type, typename... __types> requires (sizeof...(__types) > 0)
			struct ___<__type, __types...> {
				using __result = xns::conditional<sizeof(__type) * xns::bits_per_byte != __bits,
												  typename ___<__types...>::__result,
												  __type>;
			};

			/* end of recursion specialization */
			template <typename __type>
			struct ___<__type> {
				using __result = xns::conditional<sizeof(__type) * xns::bits_per_byte != __bits,
												  __error<__type>,
												  __type>;
			};


		public:

			// -- public types ------------------------------------------------

			/* type */
			using type = typename ___<__params...>::__result;

	}; // class type_selector



	/* sint type */
	template <unsigned __bits>
	using sint = typename xns::integer_selector<__bits>::signed_type;

	/* uint type */
	template <unsigned __bits>
	using uint = typename xns::integer_selector<__bits>::unsigned_type;



	/* arch address types */
	//using addr_t  = xns::uint<xns::bytes_per_address * xns::bits_per_byte>;

	/* uintptr types */
	using uintptr_t  = xns::uint<xns::bytes_per_address * xns::bits_per_byte>;


	/* signed size type */
	using ssize_t = xns::sint<xns::bytes_per_address * xns::bits_per_byte>;

	/* unsigned size type */
	using size_t = xns::uint<xns::bytes_per_address * xns::bits_per_byte>;

	/* pointer difference types */
	using ptrdiff_t = decltype(xns::declval<char*>() - xns::declval<char*>());



	/* byte types */
	using sbyte   = xns::sint<xns::bits_per_byte>;
	using ubyte   = xns::uint<xns::bits_per_byte>;

	/* 8-bit integer types */
	using s8      = xns::sint<8>;
	using u8      = xns::uint<8>;

	/* 16-bit integer types */
	using s16     = xns::sint<16>;
	using u16     = xns::uint<16>;

	/* 32-bit integer types */
	using s32     = xns::sint<32>;
	using u32     = xns::uint<32>;

	/* 64-bit integer types */
	using s64     = xns::sint<64>;
	using u64     = xns::uint<64>;

	/* 128-bit integer types */
	#ifdef XNS_128BIT_INTEGERS
	using s128    = xns::sint<128>;
	using u128    = xns::uint<128>;
	#endif




	#if defined XNS_128BIT_INTEGERS

	/* maximum signed integer type */
	using intmax_t = xns::sint<128>;

	/* maximum unsigned integer type */
	using uintmax_t = xns::uint<128>;

	#elif defined XNS_64BIT_INTEGERS

	/* maximum signed integer type */
	using intmax_t = xns::sint<64>;

	/* maximum unsigned integer type */
	using uintmax_t = xns::uint<64>;

	#elif defined XNS_32BIT_INTEGERS

	/* maximum signed integer type */
	using intmax_t = xns::sint<32>;

	/* maximum unsigned integer type */
	using uintmax_t = xns::uint<32>;

	#endif // XNS_128BIT_INTEGERS



	/* 32-bit floating point type */
	using f32 = float;

	/* 64-bit floating point type */
	using f64 = double;

} // namespace xns

#endif // XNS_TYPES_HEADER
