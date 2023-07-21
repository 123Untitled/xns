#ifndef MAKE_UNSIGNED_HEADER
#define MAKE_UNSIGNED_HEADER

#include "types.hpp"

#include "is_bool.hpp"
#include "is_enum.hpp"
#include "is_integral.hpp"
#include "is_const.hpp"
#include "is_volatile.hpp"

#include "conditional.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M A K E  U N S I G N E D --------------------------------------------


	// -- detail --------------------------------------------------------------

	namespace impl {


		template <class T>
		struct make_unsigned {


			// -- assertions --------------------------------------------------

			// check if T is an integral type
			static_assert(xns::is_integral<T> || xns::is_enum<T>, "): MAKE_UNSIGNED REQUIRES AN INTEGRAL TYPE :(");

			// check if T is not a bool
			static_assert(xns::is_bool<T> == false, "): MAKE_UNSIGNED DOES NOT SUPPORT BOOL :(");


			// -- types -------------------------------------------------------

			/* signed type */
			using unsigned_type = xns::unsign<sizeof(T)>;

			/* conditional type */
			using type = xns::conditional<xns::is_const<T>,
						 xns::conditional<xns::is_volatile<T>,
						 const volatile unsigned_type,
						 const unsigned_type>,
						 xns::conditional<xns::is_volatile<T>,
						 volatile unsigned_type,
						 unsigned_type>>;

		};

	}


	/* make unsigned */
	template <class T>
	using make_unsigned = typename impl::make_unsigned<T>::type;

}

#endif
