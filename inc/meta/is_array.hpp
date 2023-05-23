#ifndef IS_ARRAY_HEADER
#define IS_ARRAY_HEADER

#include "has_type.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- D E T A I L ---------------------------------------------------------

	namespace impl {

		/* false type */
		template <class T>
		struct is_array       : public xns::no  {};

		/* true type */
		template <class T>
		struct is_array<T[]>  : public xns::yes {};

		/* true type */
		template <class T, xns::size_t N>
		struct is_array<T[N]> : public xns::yes {};

	}


	// -- I S  A R R A Y ------------------------------------------------------

	/* is array concept */
	template <class T>
	concept is_array = impl::is_array<T>::value;


}


#endif
