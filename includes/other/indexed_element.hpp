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

#ifndef XNS_INDEXED_ELEMENT_HEADER
#define XNS_INDEXED_ELEMENT_HEADER

#include "type_traits/types.hpp"
#include "type_traits/other/type_at.hpp"
#include "type_traits/type_transformations/conditional.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- forward declarations ------------------------------------------------

	template <typename... T>
	class tuple;

	template <typename T, typename U>
	class pair;

	template <typename... T>
	class variant;



	// -- I N D E X E D  E L E M E N T ----------------------------------------

	namespace impl {

		/* indexed element */
		template <xns::size_t, typename>
		struct indexed_element;

		/* indexed element tuple specialization */
		template <xns::size_t I, typename... T>
		struct indexed_element<I, xns::tuple<T...>> {
			using type = xns::type_at<I, T...>;
		};

		/* indexed element pair specialization */
		template <xns::size_t I, typename T, typename U>
		struct indexed_element<I, xns::pair<T, U>> {
			using type = xns::conditional<I == 0, T, U>;
		};

		/* indexed element variant specialization */
		template <xns::size_t I, typename... T>
		struct indexed_element<I, xns::variant<T...>> {
			using type = xns::type_at<I, T...>;
		};

	}

	template <xns::size_t I, typename T>
	using indexed_element = typename xns::impl::indexed_element<I, T>::type;


}

#endif // INDEXED_ELEMENT_HEADER
