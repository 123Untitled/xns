#ifndef XNS_ADD_CONST_HPP
#define XNS_ADD_CONST_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- A D D  C O N S T ----------------------------------------------------

	// -- detail --------------------------------------------------------------

	namespace impl {

		/* add const */
		template <typename T>
		struct add_const          { using type = const T; };

		/* specialisation for const T */
		template <typename T>
		struct add_const<const T> { using type = const T; };

	}

	// -- interface -----------------------------------------------------------

	/* add const */
	template <class T>
	using add_const = typename impl::add_const<T>::type;

} // namespace xns

#endif // XNS_ADD_CONST_HPP