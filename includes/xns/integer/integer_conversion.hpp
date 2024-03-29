#ifndef XNS_INTEGER_CONVERSION_HEADER
#define XNS_INTEGER_CONVERSION_HEADER

// local headers
#include "xns/utility/numeric_limits.hpp"
#include "xns/type_traits/type_categories/is_integral.hpp"
#include "xns/type_traits/type_properties/is_signed.hpp"
#include "xns/type_traits/type_properties/is_unsigned.hpp"

// c++ standard library
#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- C O N V E R S I O N -------------------------------------------------

	/* unsigned / signed conversions */
	template <xns::is_integral R,
			  xns::is_integral T> requires (((xns::is_unsigned<R> and xns::is_unsigned<T>) or
											 (xns::is_signed<R>   and xns::is_signed<T>)) and
											 (sizeof(R) >= sizeof(T)))
	inline constexpr auto conversion(const T& value) noexcept -> R {
		// bigger or equal return type
		return static_cast<R>(value);
	}

	/* unsigned conversions */
	template <xns::is_unsigned_integral R,
			  xns::is_unsigned_integral T> requires (sizeof(R) < sizeof(T))
	inline constexpr auto conversion(const T& value) noexcept -> R {
		// smaller return type
		return value > xns::limits<R>::max()
			? xns::limits<R>::max()
			: static_cast<R>(value);
	}

	/* signed conversions */
	template <xns::is_signed_integral R,
			  xns::is_signed_integral T> requires (sizeof(R) < sizeof(T))
	inline constexpr auto conversion(const T& value) noexcept -> R {
		// smaller return type
		return value > xns::limits<R>::max()
			? xns::limits<R>::max()
			: value < xns::limits<R>::min()
				? xns::limits<R>::min()
				: static_cast<R>(value);
	}


	/* signed to unsigned conversion */
	template <xns::is_unsigned_integral R, xns::is_signed_integral T>
	inline constexpr auto conversion(const T& value) noexcept -> R {
		// bigger or equal return type
		if constexpr (sizeof(R) >= sizeof(T)) {
			return value < 0 ? 0
				: static_cast<R>(value);
		} else {
			// smaller return type
			return value < 0 ? 0
				: value > xns::limits<R>::max()
				? xns::limits<R>::max()
				: static_cast<R>(value);
		}
	}

	/* unsigned to signed conversion */
	template <xns::is_signed_integral R, xns::is_unsigned_integral T>
	inline constexpr auto conversion(const T& value) noexcept -> R {
		// bigger return type
		if constexpr (sizeof(R) > sizeof(T)) {
			return static_cast<R>(value);
		} else {
			// smaller or equal return type
			return value > xns::limits<R>::max()
				? xns::limits<R>::max()
				: static_cast<R>(value);
		}
	}


}

#endif // INTEGER_CONVERSION_HEADER
