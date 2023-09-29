#ifndef XNS_INTEGRAL_CONSTANT_HEADER
#define XNS_INTEGRAL_CONSTANT_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I N T E G R A L  C O N S T A N T ------------------------------------

	/* integral constant */
	template <class T, T V>
	struct integral_constant {


		// -- types -----------------------------------------------------------

		/* value type */
		using type = T;

		/* self type */
		using self = integral_constant<T, V>;


		/* compile-time value */
		static constexpr type value = V;


		/* overload type() */
		consteval operator type() const noexcept { return value; }

		/* overload intance() */
		consteval type operator()() const noexcept { return value; }

	};


	/* bool constant */
	template <bool B>
	using bool_constant = integral_constant<bool, B>;


	// -- T R U E  T Y P E -----------------------------------------------------

	// true type
	using yes = bool_constant<true>;


	// -- F A L S E  T Y P E ---------------------------------------------------

	// false type
	using no = bool_constant<false>;

}


#endif
