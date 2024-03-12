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

#ifndef XNS_LITERAL_MAP_HEADER
#define XNS_LITERAL_MAP_HEADER

#include "type_traits/supported_operations/is_trivially_default_constructible.hpp"
#include "type_traits/supported_operations/is_nothrow_default_constructible.hpp"
#include "type_traits/supported_operations/is_nothrow_copy_constructible.hpp"
#include "type_traits/supported_operations/is_nothrow_move_constructible.hpp"
#include "type_traits/supported_operations/is_nothrow_constructible.hpp"
#include "type_traits/supported_operations/is_nothrow_copy_assignable.hpp"
#include "type_traits/supported_operations/is_nothrow_move_assignable.hpp"

//#include "is_char.hpp"
#include "is_all_unique.hpp"
#include "char_sequence.hpp"
#include "string_literal.hpp"
#include "forward.hpp"
#include "move.hpp"



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- L I T E R A L  M A P ------------------------------------------------

	template <typename T, xns::basic_string_literal... L>
	class literal_map final {


		private:

			// -- forward declarations ----------------------------------------

			template <typename>
			struct __element;


			// -- private types -----------------------------------------------

			/* key helper */
			template <xns::basic_string_literal __literal>
			using __key = xns::make_character_sequence<__literal>;

			/* element by key */
			template <xns::basic_string_literal __literal>
			using element_by_key = __element<__key<__literal>>;


			// -- private constants -------------------------------------------

			/* __have_key */
			template <xns::basic_string_literal __literal>
			static constexpr bool __have_key = xns::is_one_of<__key<__literal>, __key<L>...>;


		// -- assertions ------------------------------------------------------

		/* check all string literals are unique */
		static_assert(xns::is_all_unique<__key<L>...>,
					 "literal_map: all string literals must be unique");

		/* check for map size */
		static_assert(sizeof...(L) > 0,
					"Map must have at least one element.");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::literal_map<T, L...>;

			/* value type */
			using value_type = T;

			/* mutable reference type */
			using mut_ref = value_type&;

			/* move reference type */
			using move_ref = value_type&&;

			/* const reference type */
			using const_ref = const value_type&;

			/* size type */
			using size_type = xns::size_t;


		private:

			// -- private structs ---------------------------------------------

			/* __element */
			template <typename __sequence>
			struct __element {


				// -- types ---------------------------------------------------

				/* self type */
				using __self = __element<__sequence>;


				// -- lifecycle -----------------------------------------------

				/* explicit default constructor */
				constexpr __element(void) noexcept(xns::is_nothrow_default_constructible<value_type>)
				requires (not xns::is_trivially_default_constructible<value_type>)
				: _data{} {
				}

				/* implicit default constructor */
				constexpr __element(void) noexcept(xns::is_nothrow_default_constructible<value_type>)
				requires (xns::is_trivially_default_constructible<value_type>) = default;

				/* copy constructor */
				constexpr __element(const __self&)
				noexcept(xns::is_nothrow_move_constructible<value_type>) = default;

				/* move constructor */
				constexpr __element(__self&&)
				noexcept(xns::is_nothrow_move_constructible<value_type>) = default;

				/* variadic constructor */
				template <typename... __params>
				constexpr __element(__params&&... params)
				: _data{xns::forward<__params>(params)...} {
				}

				/* destructor */
				__attribute__((noinline))
				~__element(void) noexcept = default;


				// -- assignment operators ------------------------------------

				/* copy assignment operator */
				constexpr auto operator=(const __self&)
				noexcept(xns::is_nothrow_copy_assignable<value_type>) -> __self& = default;

				/* move assignment operator */
				constexpr auto operator=(__self&&)
				noexcept(xns::is_nothrow_move_assignable<value_type>) -> __self& = default;


				// -- members -------------------------------------------------

				/* value */
				value_type _data;

			}; // struct __element


			/* __impl */
			struct __impl final : public __element<__key<L>>... {

				// -- types ---------------------------------------------------

				/* self type */
				using __self = __impl;


				// -- lifecycle -----------------------------------------------

				/* default constructor */
				constexpr __impl(void) noexcept(xns::are_nothrow_default_constructible<__element<__key<L>>...>)
				requires (not xns::are_trivially_default_constructible<__element<__key<L>>...>)
				: __element<__key<L>>{}... {
				}

				/* default constructor */
				constexpr __impl(void) noexcept(xns::are_nothrow_default_constructible<__element<__key<L>>...>)
				requires (xns::are_trivially_default_constructible<__element<__key<L>>...>) = default;


				/* variadic constructor */
				template <typename... __params> requires (sizeof...(__params) > 1)
				constexpr __impl(__params&&... args)
				: __element<__key<L>>{xns::forward<__params>(args)}... {
				}

				/* copy constructor */
				constexpr __impl(const __self&)
				noexcept(xns::are_nothrow_copy_constructible<__element<__key<L>>...>) = default;

				/* move constructor */
				constexpr __impl(__self&&)
				noexcept(xns::are_nothrow_move_constructible<__element<__key<L>>...>) = default;

				/* destructor */
				__attribute__((noinline))
				~__impl(void) noexcept = default;


				// -- assignment operators ------------------------------------

				/* copy assignment operator */
				auto operator=(const __self&)
				noexcept(xns::are_nothrow_copy_assignable<__element<__key<L>>...>) -> __self& = default;

				/* move assignment operator */
				auto operator=(__self&&)
				noexcept(xns::are_nothrow_move_assignable<__element<__key<L>>...>) -> __self& = default;

			}; // struct __impl


			// -- private members ---------------------------------------------

			/* implementation */
			__impl _impl;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr literal_map(void) noexcept(xns::is_nothrow_default_constructible<__impl>)
			requires (not xns::is_trivially_default_constructible<__impl>)
			: _impl{} {
			}

			/* default constructor */
			constexpr literal_map(void) noexcept(xns::is_nothrow_default_constructible<__impl>)
			requires (xns::is_trivially_default_constructible<__impl>) = default;

			/* variadic constructor */
			template <typename... __params>
			constexpr literal_map(__params&&... __args) requires (sizeof...(__args) > 1)
			: _impl{xns::forward<__params>(__args)...} {

				static_assert(sizeof...(L) == sizeof...(__args),
							"literal_map: must have exactly one value for each key.");
			}

			/* copy constructor */
			constexpr literal_map(const self&)
			noexcept(xns::is_nothrow_copy_constructible<__impl>) = default;

			/* move constructor */
			inline constexpr literal_map(self&&)
			noexcept(xns::is_nothrow_move_constructible<__impl>) = default;

			/* destructor */
			~literal_map(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self&)
			noexcept(xns::is_nothrow_copy_assignable<__impl>) -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&)
			noexcept(xns::is_nothrow_move_assignable<__impl>) -> self& = default;


			// -- public accessors --------------------------------------------

			/* size */
			inline consteval auto size(void) const noexcept -> size_type {
				return sizeof...(L);
			}

			/* contains */
			constexpr auto contains(const_ref __vl) const -> bool {
				return ((__vl == static_cast<element_by_key<L>&>(_impl)._data) || ...);
			}


			// -- public loopers ----------------------------------------------

			/* for each element */
			template <typename __invokable, typename... __params>
			constexpr auto for_each(__invokable&& __func, __params&&... __args) -> void {
				(__func(static_cast<element_by_key<L>&>(_impl)._data, xns::forward<__params>(__args)...), ...);
			}

			/* for each const element */
			template <typename __invokable, typename... __params>
			constexpr auto for_each(__invokable&& __func, __params&&... __args) const -> void {
				(__func(static_cast<const element_by_key<L>&>(_impl)._data, xns::forward<__params>(__args)...), ...);
			}


		// -- friends ---------------------------------------------------------

		/* get as friend */
		template <xns::basic_string_literal ___key, typename ___type,
				  xns::basic_string_literal... ___keys>
		friend constexpr auto get(xns::literal_map<___type, ___keys...>&)
		noexcept -> ___type&;

		/* get as friend */
		template <xns::basic_string_literal ___key, typename ___type,
				  xns::basic_string_literal... ___keys>
		friend constexpr auto get(xns::literal_map<___type, ___keys...>&&)
		noexcept -> ___type&&;

		/* get as friend */
		template <xns::basic_string_literal ___key, typename ___type,
				  xns::basic_string_literal... ___keys>
		friend constexpr auto get(const xns::literal_map<___type, ___keys...>&)
		noexcept -> const ___type&;

		/* get as friend */
		template <xns::basic_string_literal ___key, typename ___type,
				  xns::basic_string_literal... ___keys>
		friend constexpr auto get(const xns::literal_map<___type, ___keys...>&&)
		noexcept -> const ___type&&;

	};


	/* get */
	template <xns::basic_string_literal __key, typename __type, xns::basic_string_literal... __keys>
	constexpr auto get(xns::literal_map<__type, __keys...>& __ltmp) noexcept -> __type& {
		// literal map type
		using __map = xns::literal_map<__type, __keys...>;
		// assertions
		static_assert(__map::template __have_key<__key>, "literal_map: key not found");
		// element type
		using __element = typename __map::template element_by_key<__key>;
		// return lvalue reference
		return static_cast<__type&>(static_cast<__element&>(__ltmp._impl)._data);
	}

	/* get */
	template <xns::basic_string_literal __key, typename __type, xns::basic_string_literal... __keys>
	constexpr auto get(xns::literal_map<__type, __keys...>&& __ltmp) noexcept -> __type&& {
		// literal map type
		using __map = xns::literal_map<__type, __keys...>;
		// assertions
		static_assert(__map::template __have_key<__key>, "literal_map: key not found");
		// element type
		using __element = typename __map::template element_by_key<__key>;
		// return rvalue reference
		return static_cast<__type&&>(static_cast<__element&&>(__ltmp._impl)._data);
	}

	/* get */
	template <xns::basic_string_literal __key, typename __type, xns::basic_string_literal... __keys>
	constexpr auto get(const xns::literal_map<__type, __keys...>& __ltmp) noexcept -> const __type& {
		// literal map type
		using __map = xns::literal_map<__type, __keys...>;
		// assertions
		static_assert(__map::template __have_key<__key>, "literal_map: key not found");
		// element type
		using __element = typename __map::template element_by_key<__key>;
		// return const lvalue reference
		return static_cast<const __type&>(static_cast<const __element&>(__ltmp._impl)._data);
	}

	/* get */
	template <xns::basic_string_literal __key, typename __type, xns::basic_string_literal... __keys>
	constexpr auto get(const xns::literal_map<__type, __keys...>&& __ltmp) noexcept -> const __type&& {
		// literal map type
		using __map = xns::literal_map<__type, __keys...>;
		// assertions
		static_assert(__map::template __have_key<__key>, "literal_map: key not found");
		// element type
		using __element = typename __map::template element_by_key<__key>;
		// return const rvalue reference
		return static_cast<const __type&&>(static_cast<const __element&&>(__ltmp._impl)._data);
	}

} // namespace xns

#endif // XNS_LITERAL_MAP_HEADER
