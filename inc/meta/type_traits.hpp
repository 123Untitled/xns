#ifndef TYPE_TRAITS_HEADER
#define TYPE_TRAITS_HEADER

#include "types.hpp"
#include "integral_constant.hpp"
#include "enable_if.hpp"

#include "is_signed.hpp"
#include "is_integral.hpp"
#include "is_lvalue_reference.hpp"
#include "is_same.hpp"

#include "remove_cv.hpp"
#include "remove_reference.hpp"

#include "move.hpp"
#include "forward.hpp"

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- A L L  O F ----------------------------------------------------------

	/* all of */
	template <bool...>
	struct all_of {
		// alias value to true
		static constexpr bool value = true;
	};

	/* all of for false */
	template <bool B, bool... Bs>
	struct all_of<B, Bs...> {
		// alias value to false
		static constexpr bool value = false;
	};

	/* all of for true */
	template <bool... Bs>
	struct all_of<true, Bs...> {
		// alias value to all of Bs
		static constexpr bool value = all_of<Bs...>::value;
	};








	template<std::size_t N, typename T, typename... types>
	struct get_Nth_type {
		using type = typename get_Nth_type<N - 1, types...>::type;
	};

	template<typename T, typename... types>
	struct get_Nth_type<0, T, types...> {
		using type = T;
	};





	// -- C H A R A C T E R  T Y P E ------------------------------------------

	template <typename T>
	struct is_char_t           : false_t {};

	template <>
	struct is_char_t<char>     : true_t {};

	template <>
	struct is_char_t<wchar_t>  : true_t {};

	template <>
	struct is_char_t<char8_t>  : true_t {};

	template <>
	struct is_char_t<char16_t> : true_t {};

	template <>
	struct is_char_t<char32_t> : true_t {};


	// -- C O N J U N C T I O N -----------------------------------------------

   // template<class...>
   // struct conjunction : std::true_type { };

   // template<class B1>
   // struct conjunction<B1> : B1 { };

   // template<class B1, class... Bn>
   // struct conjunction<B1, Bn...>
   // : std::conditional_t<bool(B1::value), conjunction<Bn...>, B1> {};




	// -- I S  8  B I T -------------------------------------------------------

	/* is 8 bit */
	template <class T>
	struct is_8bit : Xf::integral_constant<bool, sizeof(T) == 1> {};

	template <class T>
	inline constexpr bool is_8bit_v = is_8bit<T>::value;

	template <class T>
	concept is_8bit_c = is_8bit_v<T>;


	/* is 16 bit */
	template <class T>
	struct is_16bit : Xf::integral_constant<bool, sizeof(T) == 2> {};

	/* is 32 bit */
	template <class T>
	struct is_32bit : Xf::integral_constant<bool, sizeof(T) == 4> {};

	/* is 64 bit */
	template <class T>
	struct is_64bit : Xf::integral_constant<bool, sizeof(T) == 8> {};

	/* is 128 bit */
	template <class T>
	struct is_128bit : Xf::integral_constant<bool, sizeof(T) == 16> {};

	/* is 256 bit */
	template <class T>
	struct is_256bit : Xf::integral_constant<bool, sizeof(T) == 32> {};










	// enable for 8 bit type
	template <typename T>
	using enable_if_8bit = enable_if_t<is_8bit<T>::value, T>;


} // end of namespace Xf




			//template <UInt64 N, typename... A>
			//struct At_least {
			//	static constexpr bool state = sizeof...(A) <= N;
			//};

			//template <bool B>
			//struct conditional;

			//template <>
			//struct conditional<true> { using value = true_t; };

			//template <>
			//struct conditional<false> { using value = false_t; };

			//template <UInt64 N, typename... A>
			//using At_least_b = typename conditional<At_least<N, A...>::state>::value;



#endif
