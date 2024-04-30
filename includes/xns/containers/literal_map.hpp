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

#include "xns/type_traits/supported_operations/is_trivially_default_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_default_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_copy_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_copy_assignable.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_assignable.hpp"

#include "xns/type_traits/other/is_all_unique.hpp"
#include "xns/type_traits/sequences/char_sequence.hpp"
#include "xns/type_traits/other/string_literal.hpp"
#include "xns/type_traits/type_operations/forward.hpp"



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- L I T E R A L  M A P ------------------------------------------------

	template <typename ___type, xns::basic_string_literal... ___literals>
	class literal_map final {


		private:

			// -- forward declarations ----------------------------------------

			template <typename>
			struct ___wrapper;


			// -- private types -----------------------------------------------

			/* self type */
			using ___self = xns::literal_map<___type, ___literals...>;

			/* key type */
			template <xns::basic_string_literal ___literal>
			using ___key = xns::make_character_sequence<___literal>;

			/* wrapper from type */
			template <xns::basic_string_literal ___literal>
			using ___wrapper_from = ___wrapper<___key<___literal>>;


			// -- private constants -------------------------------------------

			/* __have_key */
			template <xns::basic_string_literal ___literal>
			static constexpr bool ___have_key = xns::is_one_of<___key<___literal>, ___key<___literals>...>;


		// -- assertions ------------------------------------------------------

		/* check all string literals are unique */
		static_assert(xns::is_all_unique<___key<___literals>...>,
					 "literal_map: all string literals must be unique");

		/* check for map size */
		static_assert(sizeof...(___literals) > 0,
					"Map must have at least one element.");


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type = ___type;

			/* reference type */
			using reference = value_type&;

			/* const reference type */
			using const_reference = const value_type&;

			/* size type */
			using size_type = xns::size_t;


		private:

			// -- private structs ---------------------------------------------

			/* __element */
			template <typename ___sequence>
			struct ___wrapper {


				//// -- types ---------------------------------------------------
				//
				///* self type */
				//using ___self = ___wrapper<___sequence>;
				//
				//
				//// -- lifecycle -----------------------------------------------
				//
				///* explicit default constructor */
				//constexpr __element(void) noexcept(xns::is_nothrow_default_constructible<value_type>)
				//requires (not xns::is_trivially_default_constructible<value_type>)
				//: _data{} {
				//}
				//
				///* implicit default constructor */
				//constexpr __element(void) noexcept(xns::is_nothrow_default_constructible<value_type>)
				//requires (xns::is_trivially_default_constructible<value_type>) = default;
				//
				///* copy constructor */
				//constexpr __element(const __self&)
				//noexcept(xns::is_nothrow_move_constructible<value_type>) = default;
				//
				///* move constructor */
				//constexpr __element(__self&&)
				//noexcept(xns::is_nothrow_move_constructible<value_type>) = default;
				//
				///* variadic constructor */
				//template <typename... __params>
				//constexpr __element(__params&&... params)
				//: _data{xns::forward<__params>(params)...} {
				//}
				//
				///* destructor */
				//__attribute__((noinline))
				//~__element(void) noexcept = default;
				//
				//
				//// -- assignment operators ------------------------------------
				//
				///* copy assignment operator */
				//constexpr auto operator=(const __self&)
				//noexcept(xns::is_nothrow_copy_assignable<value_type>) -> __self& = default;
				//
				///* move assignment operator */
				//constexpr auto operator=(__self&&)
				//noexcept(xns::is_nothrow_move_assignable<value_type>) -> __self& = default;


				// -- members -------------------------------------------------

				/* value */
				value_type value;

			}; // struct __element


			/* __impl */
			struct ___impl final : public ___wrapper<___key<___literals>>... {


				// -- types ---------------------------------------------------

				/* self type */
				using ___self = ___self::___impl;


				// -- lifecycle -----------------------------------------------

				/* default constructor */
				constexpr ___impl(void) noexcept(xns::is_nothrow_default_constructible<value_type>)
				requires (not xns::is_trivially_default_constructible<value_type>)
				: ___wrapper<___key<___literals>>{}... {
				}

				/* default constructor */
				constexpr ___impl(void) noexcept(xns::is_nothrow_default_constructible<value_type>)
				requires (xns::is_trivially_default_constructible<value_type>) = default;

				/* variadic constructor */
				template <typename... ___params> requires (sizeof...(___params) > 1)
				constexpr ___impl(___params&&... ___args)
				noexcept(xns::is_nothrow_constructible<value_type, ___params...>)
				: ___wrapper<___key<___literals>>{xns::forward<___params>(___args)}... {
				}

				/* copy constructor */
				constexpr ___impl(const ___self&)
				noexcept(xns::is_nothrow_copy_constructible<value_type>) = default;

				/* move constructor */
				constexpr ___impl(___self&&)
				noexcept(xns::is_nothrow_move_constructible<value_type>) = default;

				/* destructor */
				constexpr ~___impl(void) noexcept = default;


				// -- assignment operators ------------------------------------

				/* copy assignment operator */
				auto operator=(const ___self&)
				noexcept(xns::is_nothrow_copy_assignable<value_type>) -> ___self& = default;

				/* move assignment operator */
				auto operator=(___self&&)
				noexcept(xns::is_nothrow_move_assignable<value_type>) -> ___self& = default;

			}; // struct ___impl


			// -- private members ---------------------------------------------

			/* implementation */
			___impl _impl;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr literal_map(void) noexcept(xns::is_nothrow_default_constructible<___impl>)
			requires (not xns::is_trivially_default_constructible<___impl>)
			: _impl{} {
			}

			/* default constructor */
			constexpr literal_map(void) noexcept(xns::is_nothrow_default_constructible<___impl>)
			requires (xns::is_trivially_default_constructible<___impl>) = default;

			/* variadic constructor */
			template <typename... ___params>
			constexpr literal_map(___params&&... ___args) requires (sizeof...(___args) > 1U)
			: _impl{xns::forward<___params>(___args)...} {

				static_assert(sizeof...(___literals) == sizeof...(___args),
							"literal_map: must have exactly one value for each key.");
			}

			/* copy constructor */
			constexpr literal_map(const ___self&)
			noexcept(xns::is_nothrow_copy_constructible<___impl>) = default;

			/* move constructor */
			constexpr literal_map(___self&&)
			noexcept(xns::is_nothrow_move_constructible<___impl>) = default;

			/* destructor */
			constexpr ~literal_map(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const ___self&)
			noexcept(xns::is_nothrow_copy_assignable<___impl>) -> ___self& = default;

			/* move assignment operator */
			constexpr auto operator=(___self&&)
			noexcept(xns::is_nothrow_move_assignable<___impl>) -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* size */
			constexpr auto size(void) const noexcept -> size_type {
				return sizeof...(___literals);
			}

			/* contains */
			constexpr auto contains(const_reference ___vl) const noexcept /* () */ -> bool {
				return ((___vl == static_cast<___wrapper_from<___literals>&>(_impl).value) || ...);
			}


			// -- public loopers ----------------------------------------------

			/* for each element */
			template <typename ___invokable, typename... ___params>
			constexpr auto for_each(___invokable&& ___func, ___params&&... ___args) -> void {
				(___func(static_cast<___wrapper_from<___literals>&>(_impl).value, xns::forward<___params>(___args)...), ...);
			}

			/* for each const element */
			template <typename ___invokable, typename... ___params>
			constexpr auto for_each(___invokable&& ___func, ___params&&... ___args) const -> void {
				(___func(static_cast<const ___wrapper_from<___literals>&>(_impl).value, xns::forward<___params>(___args)...), ...);
			}


		// -- friends ---------------------------------------------------------

		/* get as friend */
		template <xns::basic_string_literal, typename ___tp,
				  xns::basic_string_literal... ___keys>
		friend constexpr auto get(xns::literal_map<___tp, ___keys...>&) noexcept -> ___tp&;

		/* get as friend */
		template <xns::basic_string_literal, typename ___tp,
				  xns::basic_string_literal... ___keys>
		friend constexpr auto get(xns::literal_map<___tp, ___keys...>&&) noexcept -> ___tp&&;

		/* get as friend */
		template <xns::basic_string_literal, typename ___tp,
				  xns::basic_string_literal... ___keys>
		friend constexpr auto get(const xns::literal_map<___tp, ___keys...>&) noexcept -> const ___tp&;

		/* get as friend */
		template <xns::basic_string_literal, typename ___tp,
				  xns::basic_string_literal... ___keys>
		friend constexpr auto get(const xns::literal_map<___tp, ___keys...>&&) noexcept -> const ___tp&&;

	}; // class literal_map


	/* get */
	template <xns::basic_string_literal ___literal, typename ___type, xns::basic_string_literal... ___literals>
	constexpr auto get(xns::literal_map<___type, ___literals...>& ___map) noexcept -> ___type& {

		// literal map type
		using ___map_type = xns::literal_map<___type, ___literals...>;

		// assertions
		static_assert(___map_type::template ___have_key<___literal>, "literal_map: key not found");

		// wrapper type
		using ___wrapper_type = typename ___map_type::template ___wrapper_from<___literal>;

		// return lvalue reference
		return static_cast<___type&>(static_cast<___wrapper_type&>(___map._impl).value);
	}

	/* get */
	template <xns::basic_string_literal ___literal, typename ___type, xns::basic_string_literal... ___literals>
	constexpr auto get(xns::literal_map<___type, ___literals...>&& ___map) noexcept -> ___type&& {

		// literal map type
		using ___map_type = xns::literal_map<___type, ___literals...>;

		// assertions
		static_assert(___map_type::template ___have_key<___literal>, "literal_map: key not found");

		// wrapper type
		using ___wrapper_type = typename ___map_type::template ___wrapper_from<___literal>;

		// return rvalue reference
		return static_cast<___type&&>(static_cast<___wrapper_type&&>(___map._impl).value);
	}

	/* get */
	template <xns::basic_string_literal ___literal, typename ___type, xns::basic_string_literal... ___literals>
	constexpr auto get(const xns::literal_map<___type, ___literals...>& ___map) noexcept -> const ___type& {

		// literal map type
		using ___map_type = xns::literal_map<___type, ___literals...>;

		// assertions
		static_assert(___map_type::template ___have_key<___literal>, "literal_map: key not found");

		// wrapper type
		using ___wrapper_type = typename ___map_type::template ___wrapper_from<___literal>;

		// return const lvalue reference
		return static_cast<const ___type&>(static_cast<const ___wrapper_type&>(___map._impl).value);
	}

	/* get */
	template <xns::basic_string_literal ___literal, typename ___type, xns::basic_string_literal... ___literals>
	constexpr auto get(const xns::literal_map<___type, ___literals...>&& ___map) noexcept -> const ___type&& {

		// literal map type
		using ___map_type = xns::literal_map<___type, ___literals...>;

		// assertions
		static_assert(___map_type::template ___have_key<___literal>, "literal_map: key not found");

		// wrapper type
		using ___wrapper_type = typename ___map_type::template ___wrapper_from<___literal>;

		// return const rvalue reference
		return static_cast<const ___type&&>(static_cast<const ___wrapper_type&&>(___map._impl).value);
	}



	/* for each */
	template <typename ___invokable, typename ___type, xns::basic_string_literal... ___literals, typename... ___params>
	constexpr auto for_each(xns::literal_map<___type, ___literals...>& ___map, ___invokable&& ___func, ___params&&... ___args) -> void {
		___map.for_each(xns::forward<___invokable>(___func), xns::forward<___params>(___args)...);
	}



} // namespace xns

#endif // XNS_LITERAL_MAP_HEADER
