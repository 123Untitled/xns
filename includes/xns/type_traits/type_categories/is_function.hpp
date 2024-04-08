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

#ifndef XNS_IS_FUNCTION_HEADER
#define XNS_IS_FUNCTION_HEADER

#include "xns/type_traits/other/is_one_of.hpp"
#include "xns/type_traits/type_trait_constants/integral_constant.hpp"
#include "xns/type_traits/type_modifications/remove_cv.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  F U N C T I O N ------------------------------------------------


	namespace impl {

		// primary template
		template <typename>
		struct is_function : xns::false_type {};


		// specialization for regular functions
		template<typename R, typename... A>
		struct is_function<R(A...)> : xns::true_type {};


		// specialization for variadic functions such as std::printf
		template<typename R, typename... A>
		struct is_function<R(A..., ...)> : xns::true_type {};


		// specialization for function types that have cv-qualifiers
		template<typename R, typename... A>
		struct is_function<R(A...) const> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) volatile> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) const volatile> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) volatile> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const volatile> : xns::true_type {};



		// specialization for function types that have ref-qualifiers
		template<typename R, typename... A>
		struct is_function<R(A...) &> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) const &> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) volatile &> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) const volatile &> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) &> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const &> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) volatile &> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const volatile &> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) &&> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) const &&> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) volatile &&> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) const volatile &&> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) &&> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const &&> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) volatile &&> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const volatile &&> : xns::true_type {};



		// specializations for noexcept versions of all the above (C++17 and later)
		template<typename R, typename... A>
		struct is_function<R(A...) noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) const noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) volatile noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) const volatile noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) volatile noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const volatile noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) & noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) const & noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) volatile & noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) const volatile & noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) & noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const & noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) volatile & noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const volatile & noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) && noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) const && noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) volatile && noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A...) const volatile && noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) && noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const && noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) volatile && noexcept> : xns::true_type {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const volatile && noexcept> : xns::true_type {};

	}

	/* is function concept */
	template <typename T>
	concept is_function = impl::is_function<T>::value;



	// -- I S  M E M B E R  F U N C T I O N -----------------------------------


	namespace impl {

		/* is member function */
		template <typename>
		struct is_member_function : xns::false_type {};

		/* is member function specialization */
		template <typename T, typename F>
		struct is_member_function<F T::*> : impl::is_function<F> {};

	}

	/* is member function concept */
	template <typename T>
	concept is_member_function = impl::is_member_function<xns::remove_cv<T>>::value;



} // namespace xns

#endif // IS_FUNCTION_HEADER

