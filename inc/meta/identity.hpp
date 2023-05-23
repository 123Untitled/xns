#ifndef IDENTITY_HEADER
#define IDENTITY_HEADER

#include "types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I D E N T I T Y -----------------------------------------------------

	/* identity */
	template <class T>
	struct _identity {
		using type = T;
	};

	/* identity type */
	template <class T>
	using identity = typename _identity<T>::type;


	/* identity parameter pack */
	template <class... A>
	struct _identity_pack {
		using type = _identity_pack<A...>;
	};

	/* identity parameter pack type */
	template <class... A>
	using identity_pack = typename _identity_pack<A...>::type;


}


#endif
