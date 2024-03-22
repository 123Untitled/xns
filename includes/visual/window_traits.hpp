#ifndef XNS_WINDOW_TRAITS_HEADER
#define XNS_WINDOW_TRAITS_HEADER

// local headers
#include "type_traits/type_trait_constants/integral_constant.hpp"
#include "type_traits/relationships_and_property_queries/is_same.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- S P L I T  T Y P E  T R A I T S -------------------------------------

	/* vsplit type */
	struct vsplit_t {};

	/* hsplit type */
	struct hsplit_t {};

	/* is vsplit concept */
	template <class T>
	concept is_vsplit = xns::is_same<T, vsplit_t>;

	/* is hsplit concept */
	template <class T>
	concept is_hsplit = xns::is_same<T, hsplit_t>;

	/* is split concept */
	template <class T>
	concept is_split = is_vsplit<T> || is_hsplit<T>;



	// -- P A N E  T Y P E  T R A I T S ---------------------------------------

	/* pane one type */
	struct pane_one_t {};

	/* pane two type */
	struct pane_two_t {};

	/* is pane one concept */
	template <class T>
	concept is_pane_one = xns::is_same<T, pane_one_t>;

	/* is pane two concept */
	template <class T>
	concept is_pane_two = xns::is_same<T, pane_two_t>;

	/* is pane concept */
	template <class T>
	concept is_pane = is_pane_one<T> || is_pane_two<T>;



}

#endif
