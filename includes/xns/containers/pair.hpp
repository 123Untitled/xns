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

#ifndef XNS_PAIR_HEADER
#define XNS_PAIR_HEADER

// local headers
#include "xns/type_traits/supported_operations/is_nothrow_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_default_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_copy_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_copy_assignable.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_assignable.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_destructible.hpp"

#include "xns/type_traits/types.hpp"
#include "xns/type_traits/type_operations/move.hpp"
#include "xns/type_traits/type_operations/forward.hpp"

#include "xns/other/indexed_element.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- P A I R -------------------------------------------------------------

	template <typename T1, typename T2>
	class pair final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::pair<T1, T2>;

			/* first type */
			using first_type = T1;

			/* second type */
			using second_type = T2;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr pair(void)
			noexcept(xns::are_nothrow_default_constructible<T1, T2>)
			: _first{}, _second{} {}

			/* copy pair constructor */
			inline constexpr pair(const first_type& first, const second_type& second)
			noexcept(xns::are_nothrow_copy_constructible<T1, T2>)
			: _first{first}, _second{second} {}

			/* forward constructor */
			template <typename U1 = T1, typename U2 = T2>
			inline constexpr pair(U1&& t1, U2&& t2)
			noexcept(xns::is_nothrow_constructible<first_type, U1>
				  && xns::is_nothrow_constructible<second_type, U2>)
			: _first{xns::forward<U1>(t1)}, _second{xns::forward<U2>(t2)} {}

			/* copy constructor */
			constexpr pair(const self&)
			noexcept(xns::are_nothrow_copy_constructible<T1, T2>) = default;

			/* move constructor */
			constexpr pair(self&&)
			noexcept(xns::are_nothrow_move_constructible<T1, T2>) = default;

			/* destructor */
			~pair(void) noexcept(xns::are_nothrow_destructible<T1, T2>) {/* error here if we set to = default */}


			// -- public assignment operators ---------------------------------

			/* copy operator */
			constexpr auto operator=(const self&)
			noexcept(xns::are_nothrow_copy_assignable<T1, T2>) -> self& = default;

			/* move operator */
			constexpr auto operator=(self&&)
			noexcept(xns::are_nothrow_move_assignable<T1, T2>) -> self& = default;


		private:
		public:

			// -- private members ---------------------------------------------

			/* first */
			first_type _first;

			/* second */
			second_type _second;


			// -- friends -----------------------------------------------------

			/* get mutable reference to first as friend */
			template <typename A, typename B>
			friend inline constexpr auto get(xns::pair<A, B>&) noexcept -> A&;

			/* get mutable reference to second as friend */
			template <typename A, typename B>
			friend inline constexpr auto get(xns::pair<B, A>&) noexcept -> A&;


			/* get const reference to first as friend */
			template <typename A, typename B>
			friend inline constexpr auto get(const xns::pair<A, B>&) noexcept -> const A&;

			/* get const reference to second as friend */
			template <typename A, typename B>
			friend inline constexpr auto get(const xns::pair<B, A>&) noexcept -> const A&;


			/* get mutable rvalue reference to first as friend */
			template <typename A, typename B>
			friend inline constexpr auto get(xns::pair<A, B>&&) noexcept -> A&&;

			/* get mutable rvalue reference to second as friend */
			template <typename A, typename B>
			friend inline constexpr auto get(xns::pair<B, A>&&) noexcept -> A&&;


			/* get const rvalue reference to first as friend */
			template <typename A, typename B>
			friend inline constexpr auto get(const xns::pair<A, B>&&) noexcept -> const A&&;

			/* get const rvalue reference to second as friend */
			template <typename A, typename B>
			friend inline constexpr auto get(const xns::pair<B, A>&&) noexcept -> const A&&;


			/* get indexed mutable reference as friend */
			template <xns::size_t I, typename A, typename B>
			friend inline constexpr auto get(xns::pair<A, B>&) noexcept -> xns::indexed_element<I, xns::pair<A, B>>&;

			/* get indexed const reference as friend */
			template <xns::size_t I, typename A, typename B>
			friend inline constexpr auto get(const xns::pair<A, B>&) noexcept -> const xns::indexed_element<I, xns::pair<A, B>>&;

			/* get indexed mutable rvalue reference as friend */
			template < xns::size_t I, typename A, typename B>
			friend inline constexpr auto get(xns::pair<A, B>&&) noexcept -> xns::indexed_element<I, xns::pair<A, B>>&&;

			/* get indexed const rvalue reference as friend */
			template < xns::size_t I, typename A, typename B>
			friend inline constexpr auto get(const xns::pair<A, B>&&) noexcept -> const xns::indexed_element<I, xns::pair<A, B>>&&;

	};



	// -- G E T  S P E C I A L I Z A T I O N S --------------------------------

	/* get mutable reference to first */
	template <typename T, typename U>
	inline constexpr auto get(xns::pair<T, U>& pair) noexcept -> T& {
		return pair._first;
	}

	/* get mutable reference to second */
	template <typename T, typename U>
	inline constexpr auto get(xns::pair<U, T>& pair) noexcept -> T& {
		return pair._second;
	}

	/* get const reference to first */
	template <typename T, typename U>
	inline constexpr auto get(const xns::pair<T, U>& pair) noexcept -> const T& {
		return pair._first;
	}

	/* get const reference to second */
	template <typename T, typename U>
	inline constexpr auto get(const xns::pair<U, T>& pair) noexcept -> const T& {
		return pair._second;
	}

	/* get mutable rvalue reference to first */
	template <typename T, typename U>
	inline constexpr auto get(xns::pair<T, U>&& pair) noexcept -> T&& {
		return xns::move(pair._first);
	}

	/* get mutable rvalue reference to second */
	template <typename T, typename U>
	inline constexpr auto get(xns::pair<U, T>&& pair) noexcept -> T&& {
		return xns::move(pair._second);
	}

	/* get const rvalue reference to first */
	template <typename T, typename U>
	inline constexpr auto get(const xns::pair<T, U>&& pair) noexcept -> const T&& {
		return xns::move(pair._first);
	}

	/* get const rvalue reference to second */
	template <typename T, typename U>
	inline constexpr auto get(const xns::pair<U, T>&& pair) noexcept -> const T&& {
		return xns::move(pair._second);
	}


	/* get indexed mutable reference */
	template <xns::size_t I, typename T1, typename T2>
    inline constexpr auto get(xns::pair<T1, T2>& pair) noexcept -> xns::indexed_element<I, xns::pair<T1, T2>>& {
		// check index
		static_assert(I < 2, "): PAIR: INDEX OUT OF BOUNDS! :(");
		if constexpr (I == 0) {
			return pair._first;
		} else { return pair._second; }
	}

	/* get indexed const reference */
	template <xns::size_t I, typename T1, typename T2>
    inline constexpr auto get(const xns::pair<T1, T2>& pair) noexcept -> const xns::indexed_element<I, xns::pair<T1, T2>>& {
		// check index
		static_assert(I < 2, "): PAIR: INDEX OUT OF BOUNDS! :(");
		if constexpr (I == 0) {
			return pair._first;
		} else { return pair._second; }
	}

	/* get indexed mutable rvalue reference */
	template < xns::size_t I, typename T1, typename T2>
    inline constexpr auto get(xns::pair<T1, T2>&& pair) noexcept -> xns::indexed_element<I, xns::pair<T1, T2>>&& {
		// check index
		static_assert(I < 2, "): PAIR: INDEX OUT OF BOUNDS! :(");
		if constexpr (I == 0) {
			return pair._first;
		} else { return pair._second; }
	}

	/* get indexed const rvalue reference */
	template < xns::size_t I, typename T1, typename T2>
    inline constexpr auto get(const xns::pair<T1, T2>&& pair) noexcept -> const xns::indexed_element<I, xns::pair<T1, T2>>&& {
		// check index
		static_assert(I < 2, "): PAIR: INDEX OUT OF BOUNDS! :(");
		if constexpr (I == 0) {
			return pair._first;
		} else { return pair._second; }
	}




			/* here from std::reference */

			// template <class U1, class U2>
			// inline constexpr pair(pair<U1, U2>& pair);

			// template <class U1, class U2>
			// constexpr pair(pair<U1, U2>&& pair);

			// template <class U1, class U2>
			// constexpr pair(const pair<U1, U2>& pair);

			// template <class U1, class U2>
			// constexpr pair(const pair<U1, U2>&& pair);

			/* end here from std::reference */



}

#endif
