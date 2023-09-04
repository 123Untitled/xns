#ifndef TYPES_HEADER
#define TYPES_HEADER

#include "conditional.hpp"
#include "is_signed.hpp"
#include "always_false.hpp"

// include for struct winsize
#include <sys/ioctl.h>
// include for declval
#include "declval.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	/* get max size of parameter pack */
	template <class... A>
	consteval auto size_of_max(void) -> decltype(sizeof(0)) {
		decltype(sizeof(0)) size = 0;
		((size = (sizeof(A) > size ? sizeof(A) : size)), ...);
		return size;
	}


	/* get max alignment of parameter pack */
	template <class... A>
	consteval auto align_of_max(void) -> decltype(sizeof(0)) {
		decltype(sizeof(0)) align = 0;
		((align = (alignof(A) > align ? alignof(A) : align)), ...);
		return align;
	}




	// -- C H A R  B I T ------------------------------------------------------

	namespace impl {

		/* get the number of bits in a char */
		consteval auto char_bit(void) noexcept -> decltype(sizeof(int)) {
			unsigned char byte{1};
			decltype(sizeof(int)) count{0};
			while (byte) {
				byte <<= 1;
				++count;
			}
			return count;
		}

	}

	/* architecture bytes */
	#define XNS_ARCH_BYTES (sizeof(void*))

	/* bits per byte */
	#define XNS_CHAR_BIT (xns::impl::char_bit())



	// -- T Y P E S -------------------------------------------------------------

	/* terminal size type */
	using term_size = decltype(xns::declval<struct winsize>().ws_row);

	/* null pointer type */
	using null = decltype(nullptr);

	/* void type */
//	template <class...>
//	using void_t = void;




	/* unsigned integer types */
	template <decltype(sizeof(void*)) N>
	using unsign =  xns::conditional<(sizeof(unsigned char)      == N), unsigned char,
					xns::conditional<(sizeof(unsigned short)     == N), unsigned short,
					xns::conditional<(sizeof(unsigned int)       == N), unsigned int,
					xns::conditional<(sizeof(unsigned long)      == N), unsigned long,
					xns::conditional<(sizeof(unsigned long long) == N), unsigned long long,
					void > > > > >;

	/* signed integer types */
	template <decltype(sizeof(void*)) N>
	using sign =    xns::conditional<(sizeof(signed char)        == N), signed char,
					xns::conditional<(sizeof(signed short)       == N), signed short,
					xns::conditional<(sizeof(signed int)         == N), signed int,
					xns::conditional<(sizeof(signed long)        == N), signed long,
					xns::conditional<(sizeof(signed long long)   == N), signed long long,
					void > > > > >;


	// re-implementation of above (unsign and sign) using struct recursion

	struct integer_traits {

		/* size type */
		using size_type = decltype(sizeof(0));


		template <size_type BITS>
		struct find {

			static_assert(BITS % XNS_CHAR_BIT == 0,
					"): ERROR: BITS MUST BE A MULTIPLE OF XNS_CHAR_BIT! :(");

			constexpr static size_type BYTES = BITS / XNS_CHAR_BIT;

			template <typename T>
			struct compile_time_error {
				static_assert(xns::always_false<T>,
						"): THIS MACHINE DOES NOT SUPPORT THIS INTEGER TYPE! :(");
			};

			template <typename...>
			struct impl;

			template <typename T, typename... Tp>
			struct impl<T, Tp...> {
				using type = xns::conditional<sizeof(T) != BYTES,
											  typename impl<Tp...>::type,
											  T>;
			};

			template <typename T>
			struct impl<T> {
				using type = xns::conditional<sizeof(T) != BYTES,
											  compile_time_error<T>,
											  T>;
			};




		};

		template <typename T, typename U>
		using signed_priority = xns::conditional<xns::is_signed<T>, T, U>;

		template <size_type BYTES>
		using signed_type = typename find<BYTES>::template impl<signed char,
																signed short,
																signed int,
																signed long,
																signed long long
																	>::type;

		template <size_type BYTES>
		using unsigned_type = typename find<BYTES>::template impl<unsigned char,
																  unsigned short,
																  unsigned int,
																  unsigned long,
																  unsigned long long
																	  >::type;


		// in sum of two integers, find the appropriate type to store the result
		// ex:
		// char + char = short
		// char + short = int
		// char + int = long
		// short + short = int
		// short + int = long
		// etc...

		// step:
		// 1. find the largest type of the two
		// 2. check if one is signed
		// 3. find the next largest type after the largest type (signed or unsigned, depending on step 2)
		// 4. if no such type exists, return the largest type (signed or unsigned, depending on step 2)

		template <typename T, typename U>
		struct sum {

			static constexpr bool is_signed = xns::is_signed<T> || xns::is_signed<U>;

			static constexpr size_type target_size = sizeof(T) > sizeof(U)
												   ? sizeof(T) * 2
												   : sizeof(U) * 2;

			__uint128_t target = 0;
			//using type = xns::conditional<>;

		};


	};




	/* arch address types */
	using addr_t  = unsign<XNS_ARCH_BYTES>;



	/* pointer types */
	using ptr_t   = unsign<XNS_ARCH_BYTES>;


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
	using size_t = unsign<XNS_ARCH_BYTES>;

	/* maximum signed integer type */
	using ssize_t = sign<XNS_ARCH_BYTES>;


	/* maximum unsigned integer type */
	using umax = unsign<XNS_ARCH_BYTES>;

	/* maximum signed integer type */
	using smax = sign<XNS_ARCH_BYTES>;


	/* floating point types */

	/* lowest floating point type */
	using f32	 = float;

	/* highest floating point type */
	using f64	 = double;


}


#endif


