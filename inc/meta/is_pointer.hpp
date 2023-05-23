#ifndef IS_POINTER_HEADER
#define IS_POINTER_HEADER

#include "integral_constant.hpp"
#include "remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- D E T A I L ---------------------------------------------------------

	namespace impl {

		/* is pointer */
		template <class T>
		struct is_pointer        : public xns::no  {};

		/* specialisation */
		template <class T>
		struct is_pointer<T*>    : public xns::yes {};

		/* helper */
		template<class T>
		struct is_pointer_helper : public is_pointer<xns::remove_cv<T>> {};

	}


	// -- I S  P O I N T E R --------------------------------------------------

	/* is pointer concept */
	template<class T>
	concept is_pointer = impl::is_pointer_helper<T>::value;


}


#endif
