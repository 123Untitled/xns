#ifndef XNS_IDENTITY_HEADER
#define XNS_IDENTITY_HEADER



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I D E N T I T Y -----------------------------------------------------

	// -- detail --------------------------------------------------------------

	namespace impl {


		/* identity */
		template <typename T>
		struct identity {
			using type = T;
		};

		/* identity parameter pack */
		template <typename... A>
		struct identity_pack {
			using type = identity_pack<A...>;
		};

	}


	/* identity type */
	template <class T>
	using identity = typename impl::identity<T>::type;

	/* identity parameter pack type */
	template <class... A>
	using identity_pack = typename impl::identity_pack<A...>::type;


}


#endif
