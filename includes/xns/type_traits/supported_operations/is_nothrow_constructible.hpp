/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_IS_NOTHROW_CONSTRUCTIBLE_HEADER
#define XNS_IS_NOTHROW_CONSTRUCTIBLE_HEADER

#include "xns/config/config.hpp"

#if not ___xns_has_builtin(__is_nothrow_constructible)
#	warning "compiler does not support __is_nothrow_constructible"
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  N O T H R O W  C O N S T R U C T I B L E ------------------------

#if ___xns_has_builtin(__is_nothrow_constructible)

	/* is nothrow constructible */
	template <typename ___type, typename... ___params>
	concept is_nothrow_constructible = __is_nothrow_constructible(___type, ___params...);

#else

	template <bool, bool, typename, typename...>
	struct ___is_nothrow_constructible;

	template <typename ___type, typename... ___params>
	struct ___is_nothrow_constructible</* is constructible */true, /* is reference */false, ___type, ___params...> {
	};

	template <typename ___type>
	auto ___test(___type) noexcept -> void {
	}

	template <typename ___type, typename ___param>
	struct ___is_nothrow_constructible</* is constructible */true, /* is reference */true, ___type, ___param> {
	};

	template <typename ___type, bool ___is_ref, typename... ___params>
	struct ___is_nothrow_constructible</* is constructible */false, ___is_ref, ___type, ___params...> : public xns::false_type {
	};





#endif


} // namespace xns

#endif // XNS_IS_NOTHROW_CONSTRUCTIBLE_HEADER
