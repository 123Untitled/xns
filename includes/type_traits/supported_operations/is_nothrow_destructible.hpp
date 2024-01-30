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

#ifndef XNS_IS_NOTHROW_DESTRUCTIBLE_HPP
#define XNS_IS_NOTHROW_DESTRUCTIBLE_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  N O T H R O W  D E S T R U C T I B L E ----------------------------

	/* is nothrow destructible */
	template <typename T>
	concept is_nothrow_destructible = __is_nothrow_destructible(T);

	/* are nothrow destructible */
	template <typename... T>
	concept are_nothrow_destructible = (xns::is_nothrow_destructible<T> && ...);

} // namespace xns

#endif // XNS_IS_NOTHROW_DESTRUCTIBLE_HPP




/*



_LIBCPP_BEGIN_NAMESPACE_STD

#if !defined(_LIBCPP_CXX03_LANG)

template <bool, class _Tp>
struct __libcpp_is_nothrow_destructible;

template <class _Tp>
struct __libcpp_is_nothrow_destructible<false, _Tp> : public false_type {};

template <class _Tp>
struct __libcpp_is_nothrow_destructible<true, _Tp>
    : public integral_constant<bool, noexcept(std::declval<_Tp>().~_Tp()) > {};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_destructible
    : public __libcpp_is_nothrow_destructible<is_destructible<_Tp>::value, _Tp> {};

template <class _Tp, size_t _Ns>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_destructible<_Tp[_Ns]> : public is_nothrow_destructible<_Tp> {};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_destructible<_Tp&> : public true_type {};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_destructible<_Tp&&> : public true_type {};

#else

template <class _Tp>
struct __libcpp_nothrow_destructor : public integral_constant<bool, is_scalar<_Tp>::value || is_reference<_Tp>::value> {
};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_destructible : public __libcpp_nothrow_destructor<__remove_all_extents_t<_Tp> > {
};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS is_nothrow_destructible<_Tp[]> : public false_type {};

#endif

#if _LIBCPP_STD_VER >= 17
template <class _Tp>
inline constexpr bool is_nothrow_destructible_v = is_nothrow_destructible<_Tp>::value;
#endif

_LIBCPP_END_NAMESPACE_STD


*/

