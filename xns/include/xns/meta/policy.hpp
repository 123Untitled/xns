#ifndef POLICY_HEADER
#define POLICY_HEADER

#include "move.hpp"
#include "forward.hpp"
#include "is_same.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E S T R I C T  C O N C E P T --------------------------------------

	/* locked policy */
	struct locked_t {};

	/* moveable policy */
	struct moveable_t {};

	/* copyable policy */
	struct copyable_t {};

	/* assignable policy */
	struct assignable_t {};


	/* restrict concept */
	template <class T>
	concept restrict = xns::is_same<T, assignable_t>
					|| xns::is_same<T, copyable_t>
					|| xns::is_same<T, moveable_t>
					|| xns::is_same<T, locked_t>;

	/* copyable concept */
	template <class T>
	concept copyable = xns::is_same<T, copyable_t>
					|| xns::is_same<T, assignable_t>;

	/* moveable concept */
	template <class T>
	concept moveable = xns::is_same<T, moveable_t>
					|| xns::is_same<T, assignable_t>;


	// -- S T A T I C  A S S E R T --------------------------------------------

	#define ASSERT_COPYABLE(TYPE) \
		static_assert(xns::copyable<TYPE>, "TYPE MUST BE A COPYABLE TYPE")

	#define ASSERT_MOVEABLE(TYPE) \
		static_assert(xns::moveable<TYPE>, "TYPE MUST BE A MOVEABLE TYPE")

	#define ASSERT_RESTRICT(TYPE) \
		static_assert(xns::restrict<TYPE>, "TYPE MUST BE A RESTRICT TYPE")


	// -- I S  C O N S T R U C T I B L E  C O N C E P T -----------------------

	/* is copyable */
	template <class T>
	concept is_copy_constructible = requires(T a, const T& b) {
		T{b}, a = b;
	};

	/* is moveable */
	template <class T>
	concept is_move_constructible = requires(T a, T&& b) {
		T{xns::move(b)}, a = xns::move(b);
	};

	/* is constructible */
	template <class T, class... A>
	concept is_constructible = requires(A&&... args) {
		T{xns::forward<A>(args)...};
	};



}


#endif
