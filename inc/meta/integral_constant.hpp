#ifndef INTEGRAL_CONSTANT_HEADER
#define INTEGRAL_CONSTANT_HEADER


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- I N T E G R A L  C O N S T A N T --------------------------------------

	/* integral constant */
	template <typename T, T v>
	struct integral_constant {

		/* value type */
		using value_t = T;

		/* compile-time value */
		static constexpr value_t value = v;

		/* inject value into type */
		using type = integral_constant<T, v>;

		/* overload type() */
		constexpr operator value_t() const noexcept { return value; }

		/* overload intance() */
		constexpr value_t operator()() const noexcept { return value; }

	};


	// -- T R U E  T Y P E -----------------------------------------------------

	// true type
	using true_t = integral_constant<bool, true>;


	// -- F A L S E  T Y P E ---------------------------------------------------

	// false type
	using false_t = integral_constant<bool, false>;


}

#endif
