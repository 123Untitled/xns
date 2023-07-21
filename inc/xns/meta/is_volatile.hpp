#ifndef IS_VOLATILE_HEADER
#define IS_VOLATILE_HEADER

#include "integral_constant.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  V O L A T I L E  -----------------------------------------------


	// -- detail --------------------------------------------------------------

	namespace impl {

		/* is volatile */
		template <class T>
		struct is_volatile             : xns::no  {};

		/* specialization */
		template <class T>
		struct is_volatile<volatile T> : xns::yes {};

	}


	/* is const concept */
	template <class T>
	concept is_volatile = impl::is_volatile<T>::value;



}

#endif
