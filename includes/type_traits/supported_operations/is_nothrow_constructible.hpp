/*****************************************************************************/
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*****************************************************************************/

#pragma once

#ifndef XNS_IS_NOTHROW_CONSTRUCTIBLE_HPP
#define XNS_IS_NOTHROW_CONSTRUCTIBLE_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  N O T H R O W  C O N S T R U C T I B L E ------------------------

	/* is nothrow constructible */
	template <typename T, typename... A>
	concept is_nothrow_constructible
		= __is_nothrow_constructible(T, A...);

} // namespace xns

#endif // XNS_IS_NOTHROW_CONSTRUCTIBLE_HPP


#include "integral_constant.hpp"
#include "declval.hpp"
#include <type_traits>
#include "is_reference.hpp"

namespace impl {

	template <bool, bool, typename T, typename... A>
	struct is_nothrow_constructible;

	template <typename T, typename... A>
	struct is_nothrow_constructible</*is constructible*/ true, /*is reference*/ false, T, A...>
    : public xns::bool_constant<noexcept(T(xns::declval<A>()...))> {};


	template <typename T>
	void implicit_conversion_to(T) noexcept {}


	template <typename T, typename A>
	struct is_nothrow_constructible</*is constructible*/ true, /*is reference*/ true, T, A>
    : public xns::bool_constant<noexcept(implicit_conversion_to<T>(xns::declval<A>()))> {};


	template <typename T, bool R, typename... A>
	struct is_nothrow_constructible</*is constructible*/ false, R, T, A...> : public std::false_type {};


	template <typename T, typename... A>
	struct _is_nothrow_constructible : is_nothrow_constructible<std::is_constructible<T, A...>::value,
                                        xns::is_reference<T>, T, A...> {};


	template <typename T, std::size_t N>
	struct _is_nothrow_constructible<T[N]>
    : is_nothrow_constructible<std::is_constructible<T>::value, xns::is_reference<T>, T> {};


};


