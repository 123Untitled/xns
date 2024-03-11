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

			// -- private types -----------------------------------------------

			/* key helper */
			template <xns::basic_string_literal __literal>
			using __key = xns::make_character_sequence<__literal>;


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

			template <typename __sequence>
			struct element {

				/* value */
				value_type data;

			};


			template <xns::basic_string_literal __literal>
			using element_by_key = element<__key<__literal>>;


			// -- implementation ----------------------------------------------

			struct impl final : public element<__key<L>>... {


				// -- lifecycle -----------------------------------------------

				/* default constructor */
				inline constexpr impl(void)
				: element<__key<L>>{}... {
				}

				/* variadic constructor */
				template <class... A>
				inline constexpr impl(A&&... args) requires (sizeof...(A) > 1)
				: element<__key<L>>{xns::forward<A>(args)}... {
				}

				/* copy constructor */
				inline constexpr impl(const impl& other)
				: element<__key<L>>{other}... {
				}

				/* move constructor */
				inline constexpr impl(impl&& other) noexcept
				: element<__key<L>>{xns::move(other)}... {
				}

				/* destructor */
				__attribute__((noinline))
				~impl(void) noexcept = default;


				// -- assignment operators ------------------------------------

				/* copy assignment operator */
				inline auto operator=(const impl& other) -> impl& {
					// copy other elements
					((element<__key<L>>::operator=(other)), ...);
					// return self reference
					return *this;
				}

				/* move assignment operator */
				inline auto operator=(impl&& other) noexcept -> impl& {
					// move other elements
					((element<__key<L>>::operator=(xns::move(other))), ...);
					// return self reference
					return *this;
				}


			};


			// -- private members ---------------------------------------------

			/* implementation */
			impl _impl;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline constexpr literal_map(void)
			: _impl{} {}

			/* variadic constructor */
			template <typename... A>
			inline constexpr literal_map(A&&... args) requires (sizeof...(A) > 1)
			: _impl{xns::forward<A>(args)...} {
				static_assert(sizeof...(A) == sizeof...(L),
							"Map must have exactly one value for each key.");
			}

			/* copy constructor */
			inline constexpr literal_map(const self& other)
			: _impl{other._impl} {}

			/* move constructor */
			inline constexpr literal_map(self&& other) noexcept
			: _impl{xns::move(other._impl)} {}

			/* destructor */
			~literal_map(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self& other) -> self& {
				// check for self assignment
				if (this != &other)
					return *this;
				// copy other implementation
				_impl = other._impl;
				// return self reference
				return *this;
			}

			/* move assignment operator */
			constexpr auto operator=(self&& other) noexcept -> self& {
				// check for self assignment
				if (this == &other)
					return *this;
				// move other implementation
				_impl = xns::move(other._impl);
				// return self reference
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* size */
			inline consteval auto size(void) const noexcept -> size_type {
				return sizeof...(L);
			}

			/* contains */
			constexpr auto contains(const_ref value) const -> bool {
				return ((value == _impl.element<__key<L>>::data) || ...);
			}


			// -- public modifiers --------------------------------------------

			/* clear */
			constexpr auto clear(void) -> void {
				// clear all elements
				((_impl.element<__key<L>>::data = value_type{}), ...);
			}


			// -- public loopers ----------------------------------------------

			/* for each element */
			template <typename F, typename... A>
			constexpr auto for_each(F&& f, A&&... args) -> void {
				(f(_impl.element<__key<L>>::data, xns::forward<A>(args)...), ...);
			}

			/* for each const element */
			template <typename F, typename... A>
			constexpr auto for_each(F&& f, A&&... args) const -> void {
				(f(_impl.element<__key<L>>::data, xns::forward<A>(args)...), ...);
			}



			// -- static public accessors -------------------------------------

			/* have key */
			template <xns::basic_string_literal l>
			static consteval auto have_key(void) noexcept -> bool {
				// return true if key is in map
				return xns::is_one_of<__key<l>, __key<L>...>;
			}


		// -- friends ---------------------------------------------------------

		template <xns::basic_string_literal K, typename U, xns::basic_string_literal... S>
		friend constexpr auto get(xns::literal_map<U, S...>&) noexcept -> U&;

		template <xns::basic_string_literal K, typename U, xns::basic_string_literal... S>
		friend constexpr auto get(xns::literal_map<U, S...>&&) noexcept -> U&&;

		template <xns::basic_string_literal K, typename U, xns::basic_string_literal... S>
		friend constexpr auto get(const xns::literal_map<U, S...>&) noexcept -> const U&;

		template <xns::basic_string_literal K, typename U, xns::basic_string_literal... S>
		friend constexpr auto get(const xns::literal_map<U, S...>&&) noexcept -> const U&&;

	};


	/* get */
	template <xns::basic_string_literal __key, typename __type, xns::basic_string_literal... __keys>
	constexpr auto get(xns::literal_map<__type, __keys...>& __ltmp) noexcept -> __type& {
		// literal map type
		using __map = xns::literal_map<__type, __keys...>;
		// assertions
		static_assert(__map::template have_key<__key>(), "literal_map: key not found");
		// element type
		using __element = typename __map::template element_by_key<__key>;
		// return lvalue reference
		return static_cast<__type&>(static_cast<__element&>(__ltmp._impl).data);
	}

	/* get */
	template <xns::basic_string_literal __key, typename __type, xns::basic_string_literal... __keys>
	constexpr auto get(xns::literal_map<__type, __keys...>&& __ltmp) noexcept -> __type&& {
		// literal map type
		using __map = xns::literal_map<__type, __keys...>;
		// assertions
		static_assert(__map::template have_key<__key>(), "literal_map: key not found");
		// element type
		using __element = typename __map::template element_by_key<__key>;
		// return rvalue reference
		return static_cast<__type&&>(static_cast<__element&&>(__ltmp._impl).data);
	}

	/* get */
	template <xns::basic_string_literal __key, typename __type, xns::basic_string_literal... __keys>
	constexpr auto get(const xns::literal_map<__type, __keys...>& __ltmp) noexcept -> const __type& {
		// literal map type
		using __map = xns::literal_map<__type, __keys...>;
		// assertions
		static_assert(__map::template have_key<__key>(), "literal_map: key not found");
		// element type
		using __element = typename __map::template element_by_key<__key>;
		// return const lvalue reference
		return static_cast<const __type&>(static_cast<const __element&>(__ltmp._impl).data);
	}

	/* get */
	template <xns::basic_string_literal __key, typename __type, xns::basic_string_literal... __keys>
	constexpr auto get(const xns::literal_map<__type, __keys...>&& __ltmp) noexcept -> const __type&& {
		// literal map type
		using __map = xns::literal_map<__type, __keys...>;
		// assertions
		static_assert(__map::template have_key<__key>(), "literal_map: key not found");
		// element type
		using __element = typename __map::template element_by_key<__key>;
		// return const rvalue reference
		return static_cast<const __type&&>(static_cast<const __element&&>(__ltmp._impl).data);
	}

} // namespace xns

#endif // XNS_LITERAL_MAP_HEADER
