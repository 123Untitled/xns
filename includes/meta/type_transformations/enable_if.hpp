#ifndef XNS_ENABLE_IF_HEADER
#define XNS_ENABLE_IF_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- E N A B L E  I F ----------------------------------------------------

	/* enable if */
	template <bool B, class T>
	struct _enable_if;

	/* true specialization */
	template <class T>
	struct _enable_if<true, T> { using type = T; };

	/* false specialization */
	template <class T>
	struct _enable_if<false, T> {};

	/* enable if type */
	template <bool B, class T>
	using enable_if = typename _enable_if<B, T>::type;

}

#endif
