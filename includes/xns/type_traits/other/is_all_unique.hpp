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

#ifndef XNS_IS_ALL_UNIQUE_HEADER
#define XNS_IS_ALL_UNIQUE_HEADER

#include "xns/type_traits/type_trait_constants/integral_constant.hpp"
#include "xns/type_traits/other/is_one_of.hpp"
#include "xns/type_traits/relationships_and_property_queries/is_same.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A L L  D I F F E R E N T --------------------------------------------


	// -- detail --------------------------------------------------------------

	namespace impl {


		/* is all unique */
		template <typename...>
		struct is_all_unique;

		/* is all unique specialization */
		template <typename T, typename... A>
		struct is_all_unique<T, A...> : public xns::bool_constant<
		(!xns::is_one_of<T, A...> && (is_all_unique<A...>::value)) > {};

		/* end of recursion */
		template <typename T>
		struct is_all_unique<T> : public xns::true_type {};


		/* is unique */
		template <bool, typename...>
		struct is_unique;

		/* is unique specialization */
		template <typename U, typename T, typename... Tp>
		struct is_unique<false, U, T, Tp...> : public xns::bool_constant<
		(!xns::is_same<U, T> && impl::is_unique<false, U, Tp...>::value)
		|| (xns::is_same<U, T> && impl::is_unique<true, U, Tp...>::value)
		> {};

		/* is unique specialization */
		template <typename U, typename T, typename... Tp>
		struct is_unique<true, U, T, Tp...> : public xns::bool_constant<
		(!xns::is_same<U, T> && impl::is_unique<true, U, Tp...>::value)
		|| false> {};

		/* end of recursion */
		template <typename U, typename T>
		struct is_unique<false, U, T> : public xns::bool_constant<
		true> {};

		/* end of recursion */
		template <typename U, typename T>
		struct is_unique<true, U, T> : public xns::bool_constant<
		!xns::is_same<U, T>> {};



	}


	/* is all unique concept */
	template <class... A>
	concept is_all_unique = impl::is_all_unique<A...>::value;

	/* is unique concept */
	template <class T, class... A>
	concept is_unique = impl::is_unique<false, T, A...>::value;



	// -- U N I Q U E  T Y P E S ----------------------------------------------

	/* unique types */
	template <class... A>
	struct unique_types {

		// -- assertions -------------------------------------------------------
		static_assert(is_all_unique<A...>, "): TYPES MUST BE UNIQUE :(");
	};


} // namespace xns

#endif // XNS_IS_ALL_UNIQUE_HEADER
