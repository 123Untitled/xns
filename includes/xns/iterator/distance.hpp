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

#ifndef XNS_DISTANCE_HEADER
#define XNS_DISTANCE_HEADER

#include "xns/iterator/iterator_traits.hpp"
#include "xns/type_traits/relationships_and_property_queries/is_same.hpp"

#include <iostream>

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- D I S T A N C E ------------------------------------------------------

	//namespace ___impl {
	//
	//	/* random access iterator distance */
	//	template <xns::random_access_iterator_tag t, typename ___it>
	//	constexpr auto ___distance(___it ___first, ___it ___last)
	//		noexcept -> typename xns::iterator_traits<___it>::difference_type {
	//		return ___last - ___first;
	//	}
	//
	//	/* input iterator distance */
	//	template <xns::input_iterator_tag t, typename ___it>
	//	constexpr auto ___distance(___it ___first, ___it ___last)
	//		noexcept -> typename xns::iterator_traits<___it>::difference_type {
	//
	//		typename xns::iterator_traits<___it>::difference_type ___dst = 0;
	//		for (; ___first != ___last; ++___first)
	//			++___dst;
	//		return ___dst;
	//	}
	//
	//} // namespace ___impl


	/* distance */
	template <typename ___it>
	constexpr auto distance(___it ___first, ___it ___last) noexcept -> typename xns::iterator_traits<___it>::difference_type {

		using ___tag = typename xns::iterator_traits<___it>::iterator_category;

		if constexpr (xns::is_same<___tag, xns::random_access_iterator_tag>) {
			std::cout << "fast distance\n";
			return ___last - ___first;
		}
		else {

			std::cout << "slow distance\n";
			typename xns::iterator_traits<___it>::difference_type ___dst = 0;
			for (; ___first != ___last; ++___first)
				++___dst;
			return ___dst;
		}




		//return xns::___impl::___distance<___tag>(___first, ___last);
	}

} // namespace xns

#endif // XNS_DISTANCE_HEADER
