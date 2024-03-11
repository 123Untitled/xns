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

#ifndef XNS_TUPLE_HEADER
#define XNS_TUPLE_HEADER

#include "type_traits/type_transformations/decay.hpp"
#include "type_traits/supported_operations/is_trivially_default_constructible.hpp"
#include "type_traits/supported_operations/is_nothrow_default_constructible.hpp"
#include "type_traits/supported_operations/is_nothrow_constructible.hpp"
#include "type_traits/type_properties/is_empty_base.hpp"

// local headers
//#include "types.hpp"
#include "move.hpp"
#include "forward.hpp"
#include "is_same.hpp"
#include "identity.hpp"
#include "is_all_unique.hpp"
#include "indexed_element.hpp"
#include "type_at.hpp"
#include "index_of.hpp"
#include "integer_sequence.hpp"
#include "in_place.hpp"

// c++ standard library headers
#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- T U P L E -----------------------------------------------------------

	template <typename... A>
	class tuple final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::tuple<A...>;

			/* size type */
			using size_type = decltype(sizeof...(A));


		private:

			// -- private static constants ------------------------------------

			/* size */
			static constexpr size_type num_elements = sizeof...(A);


			// -- private structs ---------------------------------------------

			/* wrapper */
			template <size_type, typename, bool>
			struct wrapper;


			/* wrapper no ebo specialization */
			template <size_type __idx, typename __value_type>
			struct wrapper<__idx, __value_type, false> {


				// -- types ---------------------------------------------------

				/* self type */
				using __self = wrapper<__idx, __value_type, false>;


				// -- constants -----------------------------------------------

				/* ebo */
				enum : bool { EBO = false };


				// -- members -------------------------------------------------

				/* value */
				__value_type value;


				/* explicit default constructor */
				constexpr wrapper(void) noexcept(xns::is_nothrow_default_constructible<__value_type>)
				requires (not xns::is_trivially_default_constructible<__value_type>)
				: value{} {
				}

				/* implicit default constructor */
				constexpr wrapper(void) noexcept(xns::is_nothrow_default_constructible<__value_type>)
				requires (xns::is_trivially_default_constructible<__value_type>) = default;


				/* value constructor */
				template <typename U>
				constexpr wrapper(U&& val) noexcept(xns::is_nothrow_constructible<__value_type, U&&>)
				: value{xns::forward<U>(val)} {
				}

				/* copy constructor */
				constexpr wrapper(const __self&) = default;

				/* move constructor */
				constexpr wrapper(__self&&) noexcept = default;

				/* destructor */
				~wrapper(void) noexcept = default;


				// -- assignment operators ------------------------------------

				/* copy assignment operator */
				constexpr auto operator=(const __self&) -> __self& = default;

				/* move assignment operator */
				constexpr auto operator=(__self&&) noexcept -> __self& = default;


				// -- comparison operators ------------------------------------

				/* equality operator */
				constexpr auto operator==(const __self&) const noexcept -> bool = default;

			}; // struct wrapper


			/* wrapper ebo specialization */
			template <size_type __idx, typename __value_type>
			struct wrapper<__idx, __value_type, true> : public __value_type {


				// -- types ---------------------------------------------------

				/* self type */
				using __self = wrapper<__idx, __value_type, true>;


				// -- constants -----------------------------------------------

				/* ebo */
				enum : bool { EBO = true };


				// -- lifecycle ----------------------------------------------

				/* default constructor */
				constexpr wrapper(void) = default;

				/* value constructor */
				template <typename U>
				constexpr wrapper(U&& val)
				: __value_type{xns::forward<U>(val)} {
				}

				/* copy constructor */
				constexpr wrapper(const __self&) = default;

				/* move constructor */
				constexpr wrapper(__self&&) noexcept = default;

				/* destructor */
				~wrapper(void) noexcept = default;


				// -- assignment operators ------------------------------------

				/* copy assignment operator */
				constexpr auto operator=(const __self&) -> __self& = default;

				/* move assignment operator */
				constexpr auto operator=(__self&&) noexcept -> __self& = default;



				// -- comparison operators ------------------------------------

				/* equality operator */
				auto constexpr operator==(const __self&) const -> bool = default;

				/* inequality operator */
				auto constexpr operator!=(const __self&) const -> bool = default;

				/* less than operator */
				auto constexpr operator<(const __self&) const -> bool = default;

				/* greater than operator */
				auto constexpr operator>(const __self&) const -> bool = default;

				/* less than or equal operator */
				auto constexpr operator<=(const __self&) const -> bool = default;

				/* greater than or equal operator */
				auto constexpr operator>=(const __self&) const -> bool = default;

			}; // struct wrapper


			/* impl */
			template <typename>
			struct impl;

			/* specialization for index sequence */
			template <size_type... __idx>
			struct impl<xns::index_sequence<__idx...>> final : public wrapper<__idx, A, xns::is_empty_base<A>>... {


				// -- public types --------------------------------------------

				/* self type */
				using __self = self::impl<xns::index_sequence<__idx...>>;


				// -- public lifecycle ----------------------------------------

				/* default constructor */
				constexpr impl(void) requires (not xns::are_trivially_default_constructible<A...>)
				: wrapper<__idx, A, __ebo<A>>{}... {
				}

				/* default constructor */
				constexpr impl(void) requires (xns::are_trivially_default_constructible<A...>) = default;

				/* variadic constructor */
				template <typename... U>
				constexpr impl(U&&... args)
				: wrapper<__idx, A, xns::is_empty_base<A>>{xns::forward<U>(args)}... {
				}

				/* copy constructor */
				constexpr impl(const __self&) = default;

				/* move constructor */
				constexpr impl(__self&&) noexcept = default;

				/* destructor */
				__attribute__((noinline))
				~impl(void) noexcept = default;


				// -- public assignment operators -----------------------------

				/* copy assignment operator */
				auto constexpr operator=(const __self&) -> __self& = default;

				/* move assignment operator */
				auto constexpr operator=(__self&&) noexcept -> __self& = default;


				// -- public comparison operators -----------------------------

				/* equality operator */
				constexpr auto operator==(const __self&) const -> bool = default;

			};



			// -- private types -----------------------------------------------

			/* sequence type */
			using sequence = xns::index_sequence_for<A...>;

			/* require ebo */
			template <typename T>
			constexpr static bool __ebo = xns::is_empty_base<T>;


			/* indexed type */
			template <size_type I>
			using indexed = xns::type_at<I, A...>;

			/* element from index */
			template <size_type I>
			using wrapper_at = wrapper<I, indexed<I>, xns::is_empty_base<indexed<I>>>;

			/* element from type */
			template <typename T>
			using wrapper_from = wrapper<xns::index_of<T, A...>(), T, xns::is_empty_base<T>>;

			/* index of type */
			template <typename T>
			static constexpr xns::size_t _index_of = xns::index_of<T, A...>();


			// -- private members ---------------------------------------------

			/* implementation */
			impl<sequence> _impl;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr tuple(void) requires (not xns::are_trivially_default_constructible<A...>)
			: _impl{} {
			}

			/* default constructor */
			constexpr tuple(void) requires (xns::are_trivially_default_constructible<A...>) = default;

			/* variadic constructor */
			template <typename... U> requires (sizeof...(U) == sizeof...(A))
			constexpr tuple(U&&... args)
			: _impl{xns::forward<U>(args)...} {
			}

			/* copy constructor */
			constexpr tuple(const self&) = default;

			/* move constructor */
			constexpr tuple(self&&) noexcept = default;

			/* destructor */
			__attribute__((noinline))
			~tuple(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self&) -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&) noexcept -> self& = default;


			// -- public comparison operators ---------------------------------

			/* equality operator */
			constexpr auto operator==(const self&) const -> bool = default;


		// -- friends ---------------------------------------------------------

		/* get reference as friend */
		template <xns::size_t I, typename... T>
		friend constexpr auto get(xns::tuple<T...>&)
		noexcept -> xns::indexed_element<I, xns::tuple<T...>>&;

		/* get rvalue reference as friend */
		template <xns::size_t I, typename... T>
		friend constexpr auto get(xns::tuple<T...>&&)
		noexcept -> xns::indexed_element<I, xns::tuple<T...>>&&;

		/* get constant reference as friend */
		template <xns::size_t I, typename... T>
		friend constexpr auto get(const xns::tuple<T...>&)
		noexcept -> const xns::indexed_element<I, xns::tuple<T...>>&;

		/* get constant rvalue reference as friend */
		template <xns::size_t I, typename... T>
		friend constexpr auto get(const xns::tuple<T...>&&)
		noexcept -> const xns::indexed_element<I, xns::tuple<T...>>&&;


		/* get reference as friend */
		template <typename U, typename... T>
		friend constexpr auto get(xns::tuple<T...>&)
		noexcept -> U&;

		/* get rvalue reference as friend */
		template <typename U, typename... T>
		friend constexpr auto get(xns::tuple<T...>&&)
		noexcept -> U&&;

		/* get constant reference as friend */
		template <typename U, typename... T>
		friend constexpr auto get(const xns::tuple<T...>&)
		noexcept -> const U&;

		/* get constant rvalue reference as friend */
		template <typename U, typename... T>
		friend constexpr auto get(const xns::tuple<T...>&&)
		noexcept -> const U&&;


		/* make tuple as friend */
		template <typename... T>
		friend constexpr auto make_tuple(T&&...) -> xns::tuple<T...>;

	}; 


	/* deduction guide */
	template <typename... A>
	tuple(A...) -> tuple<A...>;



	/* get */
	template <decltype(sizeof(0)) __idx, typename... __params>
	auto constexpr get(xns::tuple<__params...>& __tpl)
	noexcept -> xns::indexed_element<__idx, xns::tuple<__params...>>& {

		// assertions
		static_assert(__idx < sizeof...(__params), "get: index out of range");

		// wrapper type
		using __wrapper = typename xns::tuple<__params...>::template wrapper_at<__idx>;
		// return type
		using __return  = xns::indexed_element<__idx, xns::tuple<__params...>>;

		// return lvalue reference
		if constexpr (__wrapper::EBO)
			return static_cast<__return&>(static_cast<__wrapper&>(__tpl._impl));
		else
			return static_cast<__wrapper&>(__tpl._impl).value;
	}

	/* get */
	template <decltype(sizeof(0)) __idx, typename... __params>
	constexpr auto get(xns::tuple<__params...>&& __tpl)
	noexcept -> xns::indexed_element<__idx, xns::tuple<__params...>>&& {

		// assertions
		static_assert(__idx < sizeof...(__params), "get: index out of range");

		// wrapper type
		using __wrapper = typename xns::tuple<__params...>::template wrapper_at<__idx>;
		// return type
		using __return  = xns::indexed_element<__idx, xns::tuple<__params...>>;

		// return rvalue reference
		if constexpr (__wrapper::EBO)
			return static_cast<__return&&>(static_cast<__wrapper&&>(__tpl._impl));
		else
			return static_cast<__return&&>(static_cast<__wrapper&&>(__tpl._impl).value);
	}

	/* get */
	template <decltype(sizeof(0)) __idx, typename... __params>
	constexpr auto get(const xns::tuple<__params...>& __tpl)
	noexcept -> const xns::indexed_element<__idx, xns::tuple<__params...>>& {

		// assertions
		static_assert(__idx < sizeof...(__params), "get: index out of range");

		// wrapper type
		using __wrapper = typename xns::tuple<__params...>::template wrapper_at<__idx>;
		// return type
		using __return  = xns::indexed_element<__idx, xns::tuple<__params...>>;

		// return const lvalue reference
		if constexpr (__wrapper::EBO)
			return static_cast<const __return&>(static_cast<const __wrapper&>(__tpl._impl));
		else
			return static_cast<const __wrapper&>(__tpl._impl).value;
	}

	/* get */
	template <decltype(sizeof(0)) __idx, typename... __params>
	constexpr auto get(const xns::tuple<__params...>&& __tpl)
	noexcept -> const xns::indexed_element<__idx, xns::tuple<__params...>>&& {

		// assertions
		static_assert(__idx < sizeof...(__params), "get: index out of range");

		// wrapper type
		using __wrapper = typename xns::tuple<__params...>::template wrapper_at<__idx>;
		// return type
		using __return  = xns::indexed_element<__idx, xns::tuple<__params...>>;

		// return const rvalue reference
		if constexpr (__wrapper::EBO)
			return static_cast<const __return&&>(static_cast<const __wrapper&&>(__tpl._impl));
		else
			return static_cast<const __return&&>(static_cast<const __wrapper&&>(__tpl._impl).value);
	}


	namespace impl {

		template <typename... A>
		struct tuple_size;

		template <typename... A>
		struct tuple_size<xns::tuple<A...>>
		: xns::integral_constant<xns::size_t, sizeof...(A)> {};

	}

	template <typename T>
	inline constexpr auto tuple_size = impl::tuple_size<xns::remove_cvrp<T>>::value;



	/* get tuple element reference */
	template <typename U, typename... T>
	constexpr auto get(xns::tuple<T...>& __tpl) noexcept -> U& {

		// assertions
		static_assert(xns::is_one_of<U, T...>, "get: type is not in tuple");
		static_assert(xns::is_unique<U, T...>, "get: type is ambiguous, because it is not unique");

		// wrapper type
		using __wrapper = typename xns::tuple<T...>::template wrapper_from<U>;

		// return a reference to the tuple element
		if constexpr (__wrapper::EBO)
			return static_cast<U&>(static_cast<__wrapper&>(__tpl._impl));
		else
			return static_cast<__wrapper&>(__tpl._impl).value;
	}

	/* get tuple element rvalue reference */
	template <typename U, typename... T>
	constexpr auto get(xns::tuple<T...>&& __tpl) noexcept -> U&& {

		// assertions
		static_assert(xns::is_one_of<U, T...>, "get: type is not in tuple");
		static_assert(xns::is_unique<U, T...>, "get: type is ambiguous, because it is not unique");

		// wrapper type
		using __wrapper = typename xns::tuple<T...>::template wrapper_from<U>;

		// return a rvalue reference to the tuple element
		if constexpr (__wrapper::EBO)
			return static_cast<U&&>(static_cast<__wrapper&&>(__tpl._impl));
		else
			return static_cast<U&&>(static_cast<__wrapper&&>(__tpl._impl).value);
	}

	/* get constant tuple element reference */
	template< typename U, typename... T>
	constexpr auto get(const xns::tuple<T...>& tuple) noexcept -> const U& {

		// assertions
		static_assert(xns::is_one_of<U, T...>, "get: type is not in tuple");
		static_assert(xns::is_unique<U, T...>, "get: type is ambiguous, because it is not unique");

		// wrapper type
		using wrapper_type = typename xns::tuple<T...>::template wrapper_from<U>;

		// return a constant reference to the tuple element
		if constexpr (wrapper_type::EBO)
			return static_cast<const U&>(static_cast<const wrapper_type&>(tuple._impl));
		else
			return static_cast<const wrapper_type&>(tuple._impl).value;
	}

	/* get constant tuple element rvalue reference */
	template< typename U, typename... T>
	constexpr auto get(const xns::tuple<T...>&& tuple) noexcept -> const U&& {

		// assertions
		static_assert(xns::is_one_of<U, T...>, "get: type is not in tuple");
		static_assert(xns::is_unique<U, T...>, "get: type is ambiguous, because it is not unique");

		// wrapper type
		using wrapper_type = typename xns::tuple<T...>::template wrapper_from<U>;

		// return a constant rvalue reference to the tuple element
		if constexpr (wrapper_type::EBO)
			return static_cast<const U&&>(static_cast<const wrapper_type&&>(tuple._impl));
		else
			return static_cast<const U&&>(static_cast<const wrapper_type&&>(tuple._impl).value);
	}



	// -- I S  T U P L E ------------------------------------------------------

	/* detail */
	namespace __impl {

		/* is tuple false */
		template <typename __type>
		struct __is_tuple final : public xns::false_type {
			XNS_NOT_INSTANTIABLE(__is_tuple);
		};

		/* is tuple true */
		template <typename... __types>
		struct __is_tuple<xns::tuple<__types...>> final : public xns::true_type {
			XNS_NOT_INSTANTIABLE(__is_tuple);
		};

	} // namespace __impl

	/* is tuple */
	template <typename T>
	concept is_tuple = __impl::__is_tuple<xns::remove_cvrp<T>>::value;


	// -- make tuple ----------------------------------------------------------

	/* make tuple */
	template <typename... A>
	constexpr auto make_tuple(A&&... args) -> xns::tuple<A...> {
		//using tag = typename xns::tuple<A...>::private_tag;
		return xns::tuple<A...>{xns::forward<A>(args)...};
	}


	//template <typename... A>
	//auto constexpr operator==(const xns::tuple<A...>&, const xns::tuple<A...>&) -> bool {
	//	return false;
	//}



}

#endif









