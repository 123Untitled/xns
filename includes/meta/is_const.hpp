#ifndef XNS_IS_CONST_HEADER
#define XNS_IS_CONST_HEADER

#include "integral_constant.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C O N S T  -----------------------------------------------------


	// -- detail --------------------------------------------------------------

	namespace impl {

		/* is const */
		template <class T>
		struct is_const          : xns::no  {};

		/* specialization */
		template <class T>
		struct is_const<const T> : xns::yes {};

	}


	/* is const concept */
	template <class T>
	concept is_const = impl::is_const<T>::value;



}

#endif
