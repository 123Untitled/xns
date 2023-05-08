#ifndef IS_INTEGRAL_HEADER
#define IS_INTEGRAL_HEADER

#include "types.hpp"
#include "integral_constant.hpp"
#include "remove.hpp"
#include "enable_if.hpp"
#include "is_same.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- I S  I N T E G R A L ------------------------------------------------

	/* is integral */
	template <class T>
	struct is_integral :                     public false_t {};

	/* remove const */
	template <class T>
	struct is_integral<const T> :            public is_integral<T> {};

	/* remove volatile */
	template <class T>
	struct is_integral<volatile T> :         public is_integral<T> {};

	/* remove cv */
	template <class T>
	struct is_integral<volatile const T> :   public is_integral<T> {};

	template<>
	struct is_integral<char> :               public true_t {};

	template<>
	struct is_integral<signed char> :        public true_t {};

	template<>
	struct is_integral<unsigned char> :      public true_t {};

	template<>
	struct is_integral<short> :              public true_t {};

	template<>
	struct is_integral<unsigned short> :     public true_t {};

	template<>
	struct is_integral<int> :                public true_t {};

	template<>
	struct is_integral<unsigned int> :       public true_t {};

	template<>
	struct is_integral<long> :               public true_t {};

	template<>
	struct is_integral<unsigned long> :      public true_t {};

	template<>
	struct is_integral<long long> :          public true_t {};

	template<>
	struct is_integral<unsigned long long> : public true_t {};

	template<>
	struct is_integral<char8_t> :            public true_t {};

	template<>
	struct is_integral<char16_t> :           public true_t {};

	template<>
	struct is_integral<char32_t> :           public true_t {};

	template<>
	struct is_integral<wchar_t> :            public true_t {};

	template<>
	struct is_integral<bool> :               public true_t {};


	template <class T>
	inline constexpr bool is_integral_v = is_integral<T>::value;

	template <class T>
	concept integral_c = Xf::is_integral_v<T>;

	template <auto N>
	using Integral = Xf::enable_if_t<Xf::is_integral_v<decltype(N)>, decltype(N)>;



	// -- I S  F L O A T I N G  P O I N T -------------------------------------

	/* is floating point */
	template <class T>
	struct is_floating_point_s
	: Xf::bool_constant
	<
		Xf::is_same<T, Xf::remove_cv_t<T>>     ||
		Xf::is_same<T, Xf::remove_cv_t<float>> ||
		Xf::is_same<T, Xf::remove_cv_t<double>>
	> {};

	/* is floating point value */
	template <class T>
	inline constexpr bool is_floating_point = is_floating_point_s<T>::value;

	/* is floating point concept */
	template <class T>
	concept FloatingPoint = Xf::is_floating_point<T>;

}


#endif
