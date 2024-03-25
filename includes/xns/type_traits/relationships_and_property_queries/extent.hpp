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

#ifndef XNS_EXTENT_HEADER
#define XNS_EXTENT_HEADER

#include "xns/type_traits/types.hpp"
#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- E X T E N T ---------------------------------------------------------

	namespace __impl {


		/* extent for non-array types */
		template <typename __type, unsigned __dim = 0>
		struct extent final {
			XNS_NOT_INSTANTIABLE(extent);
			static constexpr xns::size_t value = 0;
		};

		/* extent for unbounded array types (first dimension) */
		template <typename __type>
		struct extent<__type[], 0U> final {
			XNS_NOT_INSTANTIABLE(extent);
			static constexpr xns::size_t value = 0;
		};

		/* extent for unbounded array types (subsequent dimensions) */
		template <typename __type, unsigned __dim>
		struct extent<__type[], __dim> final {
			XNS_NOT_INSTANTIABLE(extent);
			static constexpr xns::size_t value = extent<__type, __dim - 1>::value;
		};

		/* extent for bounded array types (first dimension) */
		template <typename __type, xns::size_t __size>
		struct extent<__type[__size], 0U> final {
			XNS_NOT_INSTANTIABLE(extent);
			static constexpr xns::size_t value = __size;
		};

		/* extent for bounded array types (subsequent dimensions) */
		template <typename __type, xns::size_t __size, unsigned __dim>
		struct extent<__type[__size], __dim> final {
			XNS_NOT_INSTANTIABLE(extent);
			static constexpr xns::size_t value = extent<__type, __dim - 1>::value;
		};

	} // namespace __impl


	/* extent */
	template <typename __type, unsigned __dim = 0>
	constexpr xns::size_t extent = __impl::extent<__type, __dim>::value;

} // namespace xns

#endif // XNS_EXTENT_HEADER
