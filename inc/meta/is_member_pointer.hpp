#ifndef IS_MEMBER_POINTER_HEADER
#define IS_MEMBER_POINTER_HEADER

#include "integral_constant.hpp"
#include "remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- D E T A I L ---------------------------------------------------------

	namespace impl {

		/* is member pointer */
		template <class T>
		struct is_member_pointer         : public xns::no  {};

		/* specialisation */
		template <class T, class U>
		struct is_member_pointer<T U::*> : public xns::yes {};

		/* helper */
		template<class T>
		struct is_member_pointer_helper  : public is_member_pointer<xns::remove_cv<T>> {};

	}


	// -- I S  M E M B E R  P O I N T E R -------------------------------------

	/* is member pointer concept */
	template<class T>
	concept is_member_pointer = impl::is_member_pointer_helper<T>::value;



}



#endif
