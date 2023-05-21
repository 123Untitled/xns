#ifndef IS_INTEGRAL_HEADER
#define IS_INTEGRAL_HEADER

#include "types.hpp"
#include "integral_constant.hpp"
#include "remove.hpp"
#include "enable_if.hpp"
#include "is_same.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  I N T E G R A L ------------------------------------------------

	/* is integral */
	template <class T>
	struct _is_integral :                     xns::no {};

	/* remove const */
	template <class T>
	struct _is_integral<const T> :            _is_integral<T> {};

	/* remove volatile */
	template <class T>
	struct _is_integral<volatile T> :         _is_integral<T> {};

	/* remove cv */
	template <class T>
	struct _is_integral<volatile const T> :   _is_integral<T> {};


	template<>
	struct _is_integral<char> :               xns::yes {};

	template<>
	struct _is_integral<signed char> :        xns::yes {};

	template<>
	struct _is_integral<unsigned char> :      xns::yes {};

	template<>
	struct _is_integral<short> :              xns::yes {};

	template<>
	struct _is_integral<unsigned short> :     xns::yes {};

	template<>
	struct _is_integral<int> :                xns::yes {};

	template<>
	struct _is_integral<unsigned int> :       xns::yes {};

	template<>
	struct _is_integral<long> :               xns::yes {};

	template<>
	struct _is_integral<unsigned long> :      xns::yes {};

	template<>
	struct _is_integral<long long> :          xns::yes {};

	template<>
	struct _is_integral<unsigned long long> : xns::yes {};

	template<>
	struct _is_integral<char8_t> :            xns::yes {};

	template<>
	struct _is_integral<char16_t> :           xns::yes {};

	template<>
	struct _is_integral<char32_t> :           xns::yes {};

	template<>
	struct _is_integral<wchar_t> :            xns::yes {};

	template<>
	struct _is_integral<bool> :               xns::yes {};


	/* is integral concept */
	template <class T>
	concept is_integral = _is_integral<T>::value;



	// -- I S  F L O A T I N G  P O I N T -------------------------------------

	/* is floating point */
	template <class T>
	struct _is_floating : xns::bool_constant<
		xns::is_same<T, xns::remove_cv<T>>     ||
		xns::is_same<T, xns::remove_cv<float>> ||
		xns::is_same<T, xns::remove_cv<double>>
	>{};

	/* is floating point concept */
	template <class T>
	concept is_floating = _is_floating<T>::value;

}


#endif
