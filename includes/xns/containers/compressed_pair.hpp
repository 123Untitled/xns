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

#ifndef XNS_COMPRESSED_PAIR_HEADER
#define XNS_COMPRESSED_PAIR_HEADER

#include "xns/type_traits/supported_operations/is_nothrow_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_default_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_copy_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_copy_assignable.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_assignable.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_destructible.hpp"

#include "xns/type_traits/type_properties/is_empty_base.hpp"
#include "xns/type_traits/relationships_and_property_queries/is_same.hpp"
#include "xns/type_traits/type_operations/forward.hpp"
#include "xns/utility/swap.hpp"

#include <type_traits> // temporary (for std::decay_t)


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- C O M P R E S S E D  P A I R  E L E M E N T -------------------------

	/* empty declaration */
	template <typename, decltype(sizeof(0)), bool>
	class compressed_pair_element;


	template <typename T, decltype(sizeof(0)) I>
	class compressed_pair_element<T, I, false> {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::compressed_pair_element<T, I, false>;

			/* value type */
			using value_type = T;

			/* mutabal reference type */
			using mut_ref = T&;

			/* const reference type */
			using const_ref = const T&;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr compressed_pair_element(void)
			noexcept(xns::is_nothrow_default_constructible<T>) = default;

			/* forward constructor */
			template <typename U> requires (xns::is_not_same<self, typename std::decay<U>::type>)
			inline constexpr explicit compressed_pair_element(U&& value)
			noexcept(xns::is_nothrow_constructible<T, U>)
			: _value{xns::forward<U>(value)} {}

			/* copy constructor */
			constexpr compressed_pair_element(const self&)
			noexcept(xns::is_nothrow_copy_constructible<T>) = default;

			/* move constructor */
			constexpr compressed_pair_element(self&&)
			noexcept(xns::is_nothrow_move_constructible<T>) = default;

			/* destructor */
			~compressed_pair_element(void)
			noexcept(xns::is_nothrow_destructible<T>) = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self&)
			noexcept(xns::is_nothrow_copy_assignable<T>) -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&)
			noexcept(xns::is_nothrow_move_assignable<T>) -> self& = default;


			// -- public accessors --------------------------------------------

			/* get */
			inline constexpr auto get(void) noexcept -> mut_ref {
				return _value;
			}

			/* get */
			inline constexpr auto get(void) const noexcept -> const_ref {
				return _value;
			}

		private:

			// -- private members ---------------------------------------------

			/* value */
			value_type _value;

	}; // class compressed_pair_element


	template <typename T, decltype(sizeof(0)) I>
	class compressed_pair_element<T, I, true> : private T {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::compressed_pair_element<T, I, true>;

			/* value type */
			using value_type = T;

			/* mutabal reference type */
			using mut_ref = T&;

			/* const reference type */
			using const_ref = const T&;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr compressed_pair_element(void)
			noexcept(xns::is_nothrow_default_constructible<T>) = default;

			/* forward constructor */
			template <typename U> requires (xns::is_not_same<self, typename std::decay<U>::type>)
			inline constexpr explicit compressed_pair_element(U&& value)
			: value_type{xns::forward<U>(value)} {
			}

			/* copy constructor */
			constexpr compressed_pair_element(const self&)
			noexcept(xns::is_nothrow_copy_constructible<T>) = default;

			/* move constructor */
			constexpr compressed_pair_element(self&&)
			noexcept(xns::is_nothrow_move_constructible<T>) = default;

			/* destructor */
			~compressed_pair_element(void)
			noexcept(xns::is_nothrow_destructible<T>) = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			inline constexpr auto operator=(const self&)
			noexcept(xns::is_nothrow_copy_assignable<T>) -> self& = default;

			/* move assignment operator */
			inline constexpr auto operator=(self&&)
			noexcept(xns::is_nothrow_move_assignable<T>) -> self& = default;


			// -- public accessors --------------------------------------------

			/* get */
			inline constexpr auto get(void) noexcept -> mut_ref {
				return *this;
			}

			/* get */
			inline constexpr auto get(void) const noexcept -> const_ref {
				return *this;
			}

	}; // class compressed_pair_element



	// -- C O M P R E S S E D  P A I R ----------------------------------------

	template <typename T1, typename T2>
	class compressed_pair : private xns::compressed_pair_element<T1, 0, xns::is_empty_base<T1>>,
							private xns::compressed_pair_element<T2, 1, xns::is_empty_base<T2>> {

		// -- assertions ------------------------------------------------------

		// require T1 and T2 to be different types
		static_assert(xns::is_not_same<T1, T2>,
				"compressed_pair requires T1 and T2 to be different types");

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::compressed_pair<T1, T2>;

			/* first base type */
			using B1  = xns::compressed_pair_element<T1, 0, xns::is_empty_base<T1>>;

			/* second base type */
			using B2  = xns::compressed_pair_element<T2, 1, xns::is_empty_base<T2>>;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline constexpr explicit compressed_pair(void)
			noexcept(xns::are_nothrow_default_constructible<T1, T2>) = default;

			/* forward constructor */
			template <typename U1, typename U2>
			inline constexpr explicit compressed_pair(U1&& t1, U2&& t2)
			noexcept(xns::is_nothrow_constructible<B1, U1>
				  && xns::is_nothrow_constructible<B2, U2>)
			: B1{xns::forward<U1>(t1)}, B2{xns::forward<U2>(t2)} {
			}

			/* copy constructor */
			constexpr compressed_pair(const self&)
			noexcept(xns::are_nothrow_copy_constructible<T1, T2>) = default;

			/* move constructor */
			constexpr compressed_pair(self&&)
			noexcept(xns::are_nothrow_move_constructible<T1, T2>) = default;

			/* destructor */
			~compressed_pair(void)
			noexcept(xns::are_nothrow_destructible<T1, T2>) = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self&)
			noexcept(xns::are_nothrow_copy_assignable<T1, T2>) -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&)
			noexcept(xns::are_nothrow_move_assignable<T1, T2>) -> self& = default;


			// -- public accessors --------------------------------------------

			/* first */
			inline constexpr auto first(void) noexcept -> typename B1::mut_ref {
				return static_cast<B1&>(*this).get();
			}

			/* const first */
			inline constexpr auto first(void) const noexcept -> typename B1::const_ref {
				return static_cast<const B1&>(*this).get();
			}

			/* second */
			inline constexpr auto second(void) noexcept -> typename B2::mut_ref {
				return static_cast<B2&>(*this).get();
			}

			/* const second */
			inline constexpr auto second(void) const noexcept -> typename B2::const_ref {
				return static_cast<const B2&>(*this).get();
			}

			/* first base */
			inline constexpr static auto first_base(self* pair) noexcept -> B1* {
				return static_cast<B1*>(pair);
			}

			/* second base */
			inline constexpr static auto second_base(self* pair) noexcept -> B2* {
				return static_cast<B2*>(pair);
			}

			/* swap */
			inline constexpr auto swap(self& other) noexcept(/* no throw swappable T1 && T2 */ true) -> void {
				xns::swap( first(), other.first());
				xns::swap(second(), other.second());
			}

	}; // class compressed_pair

} // namespace xns

#endif // XNS_COMPRESSED_PAIR_HEADER
