#ifndef IS_INTEGRAL_HEADER
#define IS_INTEGRAL_HEADER

#include "types.hpp"
#include "integral_constant.hpp"
#include "remove_cv.hpp"

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



}


#endif
