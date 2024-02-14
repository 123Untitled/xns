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

#ifndef XNS_IS_ARRAY_HPP
#define XNS_IS_ARRAY_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- detail --------------------------------------------------------------

	namespace impl {

		/* false type */
		template <typename T>
		struct is_array      final {
			static constexpr bool value = false;
		};

		/* true type */
		template <typename T>
		struct is_array<T[]> final {
			static constexpr bool value = true;
		};

		/* true type */
		template <typename T, decltype(sizeof(0)) N>
		struct is_array<T[N]> final {
			static constexpr bool value = true;
		};

	}


	// -- I S  A R R A Y ------------------------------------------------------

	/* is array concept */
	template <typename T>
	concept is_array = impl::is_array<T>::value;

} // namespace xns

#endif // XNS_IS_ARRAY_HPP
