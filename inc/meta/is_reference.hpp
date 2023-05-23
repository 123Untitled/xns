#ifndef IS_LVALUE_REFERENCE_HEADER
#define IS_LVALUE_REFERENCE_HEADER

#include "integral_constant.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- D E T A I L ---------------------------------------------------------

	namespace impl {

		/* is lvalue reference */
		template <class T>
		struct is_lvalue_reference      : public xns::no  {};

		/* specialisation */
		template <class T>
		struct is_lvalue_reference<T&>  : public xns::yes {};

		/* is rvalue reference */
		template <class T>
		struct is_rvalue_reference      : public xns::no  {};

		/* specialisation */
		template <class T>
		struct is_rvalue_reference<T&&> : public xns::yes {};

	}


	// -- I S  L V A L U E  R E F E R E N C E ---------------------------------

	/* is lvalue concept */
	template <class T>
	concept is_lvalue = impl::is_lvalue_reference<T>::value;


	// -- I S  R V A L U E  R E F E R E N C E ---------------------------------

	/* is rvalue concept */
	template <class T>
	concept is_rvalue = impl::is_rvalue_reference<T>::value;


	// -- I S  R E F E R E N C E ----------------------------------------------

	/* is reference concept */
	template <class T>
	concept is_reference = is_lvalue<T> || is_rvalue<T>;


}


#endif
