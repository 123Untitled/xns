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

#ifndef XNS_REMOVE_EXTENT_HEADER
#define XNS_REMOVE_EXTENT_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E M O V E  E X T E N T --------------------------------------------

	// -- detail --------------------------------------------------------------

	namespace impl {

		/* remove extent */
		template <typename T>
		struct remove_extent final {
			using type = T;
		};

		/* array with unknown bound specialization */
		template <typename T>
		struct remove_extent<T[]> final {
			using type = T;
		};

		/* array specialization */
		template <typename T, decltype(sizeof(0)) N>
		struct remove_extent<T[N]> final {
			using type = T;
		};

	} // namespace impl


	/* remove extent */
	template <typename T>
	using remove_extent = typename impl::remove_extent<T>::type;

} // namespace xns

#endif // XNS_REMOVE_EXTENT_HEADER
