#ifndef IS_LVALUE_REFERENCE_HEADER
#define IS_LVALUE_REFERENCE_HEADER

#include "integral_constant.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  L V A L U E  R E F E R E N C E ---------------------------------

	/* false type */
	template <class T>
	struct _is_lvalue      : xns::no {};

	/* true type */
	template <class T>
	struct _is_lvalue<T&>  : xns::yes {};

	/* is lvalue reference concept */
	template <class T>
	concept is_lvalue = _is_lvalue<T>::value;


	// -- I S  R V A L U E  R E F E R E N C E ------------------------------------

	/* false type */
	template <class T>
	struct _is_rvalue      : xns::no {};

	/* true type */
	template <class T>
	struct _is_rvalue<T&&> : xns::yes {};

	/* is rvalue reference concept */
	template <class T>
	concept is_rvalue = _is_rvalue<T>::value;

}


#endif
