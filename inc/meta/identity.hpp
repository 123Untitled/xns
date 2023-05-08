#ifndef IDENTITY_HEADER
#define IDENTITY_HEADER

#include "types.hpp"

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- I D E N T I T Y -----------------------------------------------------

	/* identity */
	template <class T>
	struct Identity {
		using type = T;
	};

	/* identity type */
	template <class T>
	using Identity_t = typename Identity<T>::type;


	// -- P A C K  I D E N T I T Y --------------------------------------------

	/* pack identity */
	template <class...>
	struct Pack {};



}

#endif
