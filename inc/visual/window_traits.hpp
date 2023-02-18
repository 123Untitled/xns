#ifndef WINDOW_TRAITS_HEADER
#define WINDOW_TRAITS_HEADER

#include "type_traits.hpp"

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- S P L I T  T Y P E  T R A I T S -------------------------------------

	/* vsplit type */
	struct vsplit_t {};

	/* hsplit type */
	struct hsplit_t {};

	/* is vsplit false */
	template <class T>
	struct is_vsplit : Xf::false_t {};

	/* is vsplit true */
	template <>
	struct is_vsplit<vsplit_t> : Xf::true_t {};

	/* is hsplit false */
	template <class T>
	struct is_hsplit : Xf::false_t {};

	/* is hsplit true */
	template <>
	struct is_hsplit<hsplit_t> : Xf::true_t {};

	/* is vsplit value */
	template <class T>
	constexpr bool is_vsplit_v = is_vsplit<T>::value;

	/* is hsplit value */
	template <class T>
	constexpr bool is_hsplit_v = is_hsplit<T>::value;

	/* vsplit concept */
	template <class T>
	concept vsplit_c = is_vsplit_v<T>;

	/* hsplit concept */
	template <class T>
	concept hsplit_c = is_hsplit_v<T>;

	/* is split concept */
	template <class T>
	concept split_c = vsplit_c<T> || hsplit_c<T>;




	// -- P A N E  T Y P E  T R A I T S ---------------------------------------

	/* pane one type */
	struct pane_one_t {};

	/* pane two type */
	struct pane_two_t {};

	/* is pane one false */
	template <class T>
	struct is_pane_one                 : Xf::false_t {};

	/* is pane one true */
	template <>
	struct is_pane_one<pane_one_t>     : Xf::true_t {};

	/* is pane two false */
	template <class T>
	struct is_pane_two                 : Xf::false_t {};

	/* is pane two true */
	template <>
	struct is_pane_two<pane_two_t>     : Xf::true_t {};

	/* is pane one value */
	template <class T>
	constexpr bool is_pane_one_v = is_pane_one<T>::value;

	/* is pane two value */
	template <class T>
	constexpr bool is_pane_two_v = is_pane_two<T>::value;

	/* pane one concept */
	template <class T>
	concept pane_one_c = is_pane_one_v<T>;

	/* pane two concept */
	template <class T>
	concept pane_two_c = is_pane_two_v<T>;

	/* pane concept */
	template <class T>
	concept pane_c = pane_one_c<T> || pane_two_c<T>;





}

#endif
