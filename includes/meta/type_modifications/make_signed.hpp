#ifndef XNS_MAKE_SIGNED_HPP
#define XNS_MAKE_SIGNED_HPP

#include "types.hpp"

#include "is_bool.hpp"
#include "is_enum.hpp"
#include "is_integral.hpp"
#include "is_const.hpp"
#include "is_volatile.hpp"

#include "conditional.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M A K E  S I G N E D ------------------------------------------------

	// -- detail --------------------------------------------------------------

	namespace impl {

		template <typename T>
		struct make_signed {

			// -- assertions --------------------------------------------------

			// check if T is an integral type
			static_assert(xns::is_integral<T> || xns::is_enum<T>,
					"make_signed requires an integral type.");

			// check if T is not a bool
			static_assert(xns::is_bool<T> == false,
					"make_signed does not support bool.");


			// -- types -------------------------------------------------------

			/* signed type */
			using signed_type = xns::_signed<sizeof(T)>;

			/* conditional type */
			using type = xns::conditional<xns::is_const<T>,
						 xns::conditional<xns::is_volatile<T>,
										  const volatile signed_type,
										  const signed_type>,
						 xns::conditional<xns::is_volatile<T>,
										  volatile signed_type,
										  signed_type>>;

		}; // struct make_signed

	} // namespace impl

	/* make signed */
	template <class T>
	using make_signed = typename impl::make_signed<T>::type;

} // namespace xns

#endif // XNS_MAKE_SIGNED_HPP
