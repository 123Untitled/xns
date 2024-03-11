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

			template <size_type, typename, bool>
			struct wrapper;

			template <size_type I, typename T>
			struct wrapper<I, T, false> {


				// -- types ---------------------------------------------------

				/* self type */
				using _self = wrapper<I, T, false>;

				/* value type */
				using value_type = T;


				// -- constants -----------------------------------------------

				/* ebo */
				enum : bool { EBO = false };


				// -- members -------------------------------------------------

				/* value */
				T value;


				/* explicit default constructor */
				constexpr wrapper(void) noexcept(xns::is_nothrow_default_constructible<T>)
				requires (not xns::is_trivially_default_constructible<T>)
				: value{} {
				}

				/* implicit default constructor */
				constexpr wrapper(void) noexcept(xns::is_nothrow_default_constructible<T>)
				requires (xns::is_trivially_default_constructible<T>) = default;


				template <typename U>
				constexpr wrapper(U&& val) noexcept(xns::is_nothrow_constructible<T, U&&>)
				: value{xns::forward<U>(val)} {
				}

				constexpr wrapper(const _self&) = default;
				constexpr wrapper(_self&&) noexcept = default;

				auto constexpr operator=(const _self&) -> _self& = default;

				auto constexpr operator=(_self&&) noexcept -> _self& = default;


				constexpr auto operator==(const _self&) const noexcept -> bool = default;

				~wrapper(void) noexcept = default;
			};


			template <size_type I, typename T>
			struct wrapper<I, T, true> : public T {


				// -- types ---------------------------------------------------

				/* self type */
				using _self = wrapper<I, T, true>;

				/* value type */
				using value_type = T;


				// -- constants -----------------------------------------------

				/* ebo */
				enum : bool { EBO = true };


				wrapper(void) = default;

				template <typename U>
				wrapper(U&& val) : T{xns::forward<U>(val)} {}

				wrapper(const _self&) = default;
				wrapper(_self&&) noexcept = default;
				auto operator=(const _self&) -> _self& = default;
				auto operator=(_self&&) noexcept -> _self& = default;

				~wrapper(void) noexcept = default;

				//constexpr auto operator==(const _self&) const noexcept -> bool = default;


				// -- comparison operators ------------------------------------

				/* equality operator */
				auto constexpr operator==(const _self& __other) const -> bool {
					return static_cast<value_type>(*this)
						== static_cast<value_type>(__other);
				}

				/* inequality operator */
				auto constexpr operator!=(const _self&) const -> bool = default;

				/* less than operator */
				auto constexpr operator<(const _self&) const -> bool = default;

				/* greater than operator */
				auto constexpr operator>(const _self&) const -> bool = default;

				/* less than or equal operator */
				auto constexpr operator<=(const _self&) const -> bool = default;

				/* greater than or equal operator */
				auto constexpr operator>=(const _self&) const -> bool = default;

			};

			/* wrapper */
			//template <size_type, typename T /*, bool EBO */>
			//struct wrapper {
			//
			//	T value;
			//
			//	wrapper(void) requires (not xns::is_trivially_default_constructible<T>)
			//	: value{} {
			//		std::cout << "wrapper ctor" << std::endl;
			//	}
			//
			//	wrapper(void) requires (xns::is_trivially_default_constructible<T>) = default;
			//
			//	template <typename U>
			//	wrapper(U&& val) : value{xns::forward<U>(val)} {}
			//
			//	wrapper(const wrapper&) = default;
			//	wrapper(wrapper&&) noexcept = default;
			//	auto operator=(const wrapper&) -> wrapper& = default;
			//	auto operator=(wrapper&&) noexcept -> wrapper& = default;
			//
			//	~wrapper(void) noexcept = default;
			//};

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
				//	return ((wrapper<I, A, xns::is_empty_base<A>>::value
				//		== other.wrapper<I, A, xns::is_empty_base<A>>::value) && ...);
				//}

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




			// -- private lifecycle -------------------------------------------



		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr tuple(void) requires (not xns::are_trivially_default_constructible<A...>)
			: _impl{} {
				std::cout << "tuple ctor" << std::endl;
			}

			/* default constructor */
			constexpr tuple(void) requires (xns::are_trivially_default_constructible<A...>) = default;

			/* variadic constructor */
			template <typename... U> requires (sizeof...(U) == sizeof...(A))
			constexpr tuple(U&&... args)
			: _impl{xns::forward<U>(args)...} {}

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



	/* get tuple element reference */
	template <xns::size_t I, typename... T>
	auto constexpr get(xns::tuple<T...>& tuple) noexcept -> xns::indexed_element<I, xns::tuple<T...>>& {

		// assertions
		static_assert(I < sizeof...(T), "get: index out of range");

		// wrapper type
		using wrapper_type = typename xns::tuple<T...>::template wrapper_at<I>;
		// return type
		using return_type = xns::indexed_element<I, xns::tuple<T...>>;

		// return a reference to the tuple element
		if constexpr (wrapper_type::EBO)
			return static_cast<return_type&>(static_cast<wrapper_type&>(tuple._impl));
		else
			return static_cast<wrapper_type&>(tuple._impl).value;
	}

	/* get tuple element rvalue reference */
	template <xns::size_t I, typename... T>
	constexpr auto get(xns::tuple<T...>&& tuple) noexcept -> xns::indexed_element<I, xns::tuple<T...>>&& {

		// assertions
		static_assert(I < sizeof...(T), "get: index out of range");

		// wrapper type
		using wrapper_type = typename xns::tuple<T...>::template wrapper_at<I>;
		// return type
		using return_type = xns::indexed_element<I, xns::tuple<T...>>;

		if constexpr (wrapper_type::EBO)
			return static_cast<return_type&&>(static_cast<wrapper_type&&>(tuple._impl));
		else
			return static_cast<return_type&&>(static_cast<wrapper_type&&>(tuple._impl).value);
	}

	/* get constant tuple element reference */
	template <xns::size_t I, typename... T>
	constexpr auto get(const xns::tuple<T...>& tuple) noexcept -> const xns::indexed_element<I, xns::tuple<T...>>& {

		// assertions
		static_assert(I < sizeof...(T), "get: index out of range");

		// wrapper type
		using wrapper_type = typename xns::tuple<T...>::template wrapper_at<I>;
		// return type
		using return_type = xns::indexed_element<I, xns::tuple<T...>>;

		if constexpr (wrapper_type::EBO)
			return static_cast<const return_type&>(static_cast<const wrapper_type&>(tuple._impl));
		else
			return static_cast<const wrapper_type&>(tuple._impl).value;
	}

	/* get constant tuple element rvalue reference */
	template <xns::size_t I, typename... T>
	constexpr auto get(const xns::tuple<T...>&& tuple) noexcept -> const xns::indexed_element<I, xns::tuple<T...>>&& {

		// assertions
		static_assert(I < sizeof...(T), "get: index out of range");

		// wrapper type
		using wrapper_type = typename xns::tuple<T...>::template wrapper_at<I>;
		// return type
		using return_type = xns::indexed_element<I, xns::tuple<T...>>;

		if constexpr (wrapper_type::EBO)
			return static_cast<const return_type&&>(static_cast<const wrapper_type&&>(tuple._impl));
		else
			return static_cast<const return_type&&>(static_cast<const wrapper_type&&>(tuple._impl).value);
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

	namespace impl {

		template <typename T>
		struct is_tuple final {
			constexpr static bool value = false;
		};

		template <typename... A>
		struct is_tuple<xns::tuple<A...>> final {
			constexpr static bool value = true;
		};

	}

	/* is tuple concept */
	template <typename T>
	concept is_tuple = impl::is_tuple<xns::remove_cvrp<T>>::value;


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









