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

#ifndef XNS_IS_DESTRUCTIBLE_HPP
#define XNS_IS_DESTRUCTIBLE_HPP

#include "config.hpp"

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

#if not XNS_HAS_BUILTIN(__is_destructible)
#	error "compiler does not support __is_destructible"
#endif


	// -- I S  D E S T R U C T I B L E ----------------------------------------

	/* is destructible */
	template <typename T>
	concept is_destructible = __is_destructible(T);

	/* are destructible */
	template <typename... T>
	concept are_destructible = (xns::is_destructible<T> && ...);

} // namespace xns

#endif // XNS_IS_DESTRUCTIBLE_HPP




/* my implementation of is_destructible */
/*template <typename T>
concept is_destructible = requires {
	{ xns::declval<T&>().~T() };
};*/


/* stdlib implementation of is_destructible */


//  if it's a reference, return true
//  if it's a function, return false
//  if it's   void,     return false
//  if it's an array of unknown bound, return false
//  Otherwise, return "declval<_Up&>().~_Up()" is well-formed
//    where _Up is remove_all_extents<_Tp>::type

//template <class>
//struct __is_destructible_apply {
//  typedef int type;
//};
//
//template <typename _Tp>
//struct __is_destructor_wellformed {
//  template <typename _Tp1>
//  static true_type __test(typename __is_destructible_apply<decltype(std::declval<_Tp1&>().~_Tp1())>::type);
//
//  template <typename _Tp1>
//  static false_type __test(...);
//
//  static const bool value = decltype(__test<_Tp>(12))::value;
//};
//
//template <class _Tp, bool>
//struct __destructible_imp;
//
//template <class _Tp>
//struct __destructible_imp<_Tp, false>
//    : public integral_constant<bool, __is_destructor_wellformed<__remove_all_extents_t<_Tp> >::value> {};
//
//template <class _Tp>
//struct __destructible_imp<_Tp, true> : public true_type {};
//
//template <class _Tp, bool>
//struct __destructible_false;
//
//template <class _Tp>
//struct __destructible_false<_Tp, false> : public __destructible_imp<_Tp, is_reference<_Tp>::value> {};
//
//template <class _Tp>
//struct __destructible_false<_Tp, true> : public false_type {};
//
//template <class _Tp>
//struct is_destructible : public __destructible_false<_Tp, is_function<_Tp>::value> {};
//
//template <class _Tp>
//struct is_destructible<_Tp[]> : public false_type {};
//
//template <>
//struct is_destructible<void> : public false_type {};
//
//#  if _LIBCPP_STD_VER >= 17
//template <class _Tp>
//inline constexpr bool is_destructible_v = is_destructible<_Tp>::value;
//#  endif
//
//#endif // __has_builtin(__is_destructible)
//
//_LIBCPP_END_NAMESPACE_STD
//
//#endif // _LIBCPP___TYPE_TRAITS_IS_DESTRUCTIBLE_H

