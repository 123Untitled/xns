#ifndef XNS_IS_CONSTRUCTIBLE_HEADER
#define XNS_IS_CONSTRUCTIBLE_HEADER

// local headers
#include "move.hpp"
#include "forward.hpp"
#include "is_convertible.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C O N S T R U C T I B L E --------------------------------------

	/* is constructible concept */
	template <class T, class... A>
	concept is_constructible = requires {
		T(xns::declval<A>()...);
	};

	/* is copy constructible concept (no implicit conversion) */
	template <class T, class... A>
	concept is_constructible_strict = requires {
		T{xns::declval<A>()...};
	};

	/* is copyable concept */
	template <class T>
	concept is_copy_constructible = xns::is_constructible<T, const T&>;

	/* is moveable concept */
	template <class T>
	concept is_move_constructible = xns::is_constructible<T, T&&>;

	/* is default constructible concept */
	template <class T>
	concept is_default_constructible = xns::is_constructible<T>;

	/* is assignable concept */
	template <class T, class U>
	concept is_assignable = requires(T t) {
		{ t = xns::declval<U>() } -> xns::is_convertible<T&>;
	};

	/* is copy assignable concept */
	template <class T>
	concept is_copy_assignable = xns::is_assignable<T, const T&>;

	/* is move assignable concept */
	template <class T>
	concept is_move_assignable = xns::is_assignable<T, T&&>;




}

#endif // IS_CONSTRUCTIBLE_HEADER




// is_nothrow_constructible
// is_nothrow_default_constructible
// is_nothrow_copy_constructible
// is_nothrow_move_constructible
// is_nothrow_assignable
// is_nothrow_copy_assignable
// is_nothrow_move_assignable
// is_nothrow_destructible

// is_trivially_copy_assignable
// is_trivially_assignable
// is_trivially_move_constructible
// is_trivially_copy_constructible
// is_trivially_default_constructible
// is_trivially_move_assignable
// is_trivially_constructible
// is_trivially_destructible
