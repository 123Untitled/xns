#ifndef IS_FUNCTION_HEADER
#define IS_FUNCTION_HEADER

#include "is_one_of.hpp"
#include "integral_constant.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  F U N C T I O N ------------------------------------------------


	namespace impl {

		// primary template
		template <typename>
		struct is_function : xns::no {};


		// specialization for regular functions
		template<typename R, typename... A>
		struct is_function<R(A...)> : xns::yes {};


		// specialization for variadic functions such as std::printf
		template<typename R, typename... A>
		struct is_function<R(A..., ...)> : xns::yes {};


		// specialization for function types that have cv-qualifiers
		template<typename R, typename... A>
		struct is_function<R(A...) const> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) volatile> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) const volatile> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) volatile> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const volatile> : xns::yes {};



		// specialization for function types that have ref-qualifiers
		template<typename R, typename... A>
		struct is_function<R(A...) &> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) const &> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) volatile &> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) const volatile &> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) &> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const &> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) volatile &> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const volatile &> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) &&> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) const &&> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) volatile &&> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) const volatile &&> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) &&> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const &&> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) volatile &&> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const volatile &&> : xns::yes {};



		// specializations for noexcept versions of all the above (C++17 and later)
		template<typename R, typename... A>
		struct is_function<R(A...) noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) const noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) volatile noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) const volatile noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) volatile noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const volatile noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) & noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) const & noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) volatile & noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) const volatile & noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) & noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const & noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) volatile & noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const volatile & noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) && noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) const && noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) volatile && noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A...) const volatile && noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) && noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const && noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) volatile && noexcept> : xns::yes {};

		template<typename R, typename... A>
		struct is_function<R(A..., ...) const volatile && noexcept> : xns::yes {};

	}

	/* is function concept */
	template <typename T>
	concept is_function = impl::is_function<T>::value;



	// -- I S  M E M B E R  F U N C T I O N -----------------------------------


	namespace impl {

		/* is member function */
		template <typename>
		struct is_member_function : xns::no {};

		/* is member function specialization */
		template <typename T, typename F>
		struct is_member_function<F T::*> : impl::is_function<F> {};

	}

	/* is member function concept */
	template <typename T>
	concept is_member_function = impl::is_member_function<xns::remove_cv<T>>::value;



}

#endif // IS_FUNCTION_HEADER

