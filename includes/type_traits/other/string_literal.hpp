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

#ifndef XNS_STRING_LITERAL_HEADER
#define XNS_STRING_LITERAL_HEADER

#include "type_traits/type_categories/is_char.hpp"
#include "type_traits/relationships_and_property_queries/is_same.hpp"
#include "type_traits/relationships_and_property_queries/is_comparable.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- C O P Y -------------------------------------------------------------

	// -- details -------------------------------------------------------------

	namespace impl {

		/* copy implementation */
		template <typename T, decltype(sizeof(0)) D, decltype(D) S, decltype(S) I>
		inline constexpr auto copy(T (&dst)[D], const T (&src)[S]) noexcept -> void {
			if constexpr (I == D or I == S){
				return;
			} else {
				dst[I] = src[I];
				xns::impl::copy<T, D, S, I + 1>(dst, src);
			}
		}

	}

	/* copy */
	template <typename T, decltype(sizeof(0)) D, decltype(D) S>
	inline constexpr auto copy(T (&dst)[D], const T (&src)[S]) noexcept -> void {
		xns::impl::copy<T, D, S, 0>(dst, src);
	}


	// -- C O M P A R E -------------------------------------------------------

	// -- details -------------------------------------------------------------

	namespace impl {

		/* compare implementation */
		template <typename T1, typename T2, decltype(sizeof(0)) S, decltype(S) I>
		inline constexpr auto compare(const T1 (&lhs)[S], const T2 (&rhs)[S]) noexcept -> signed int {
			if constexpr (I == S) {
				return 0;
			} else {
				return (lhs[I] == rhs[I])
					 ? (xns::impl::compare<T1, T2, S, I + 1>(lhs, rhs))
					 : (lhs[I] > rhs[I] ? +1 : -1);
			}
		}

	}

	/* compare */
	template <typename T1, typename T2, decltype(sizeof(0)) L, decltype(L) R>
	inline constexpr auto compare(const T1 (&lhs)[L], const T2 (&rhs)[R]) noexcept -> signed int {
		// assert that type is comparable
		static_assert(xns::is_comparable<T1, T2>, "Template parameter 'T' must be a comparable type.");
		// check for equal size
		if constexpr (L == R)
			return xns::impl::compare<T1, T2, L, 0>(lhs, rhs);
		else
			return (L > R ? +1 : -1);
	}



	// -- B A S I C  S T R I N G  L I T E R A L -------------------------------

	template<typename T, decltype(sizeof(0)) N>
	struct basic_string_literal final {

		// -- assertions ------------------------------------------------------

		/* check character type */
		static_assert(xns::is_char<T>,
				"Template parameter 'T' must be a character type.");

		/* check for null size */
		static_assert(N > 0,
				"Template parameter 'N' must be greater than zero.");


		// -- public types ------------------------------------------------

		/* self type */
		using self = xns::basic_string_literal<T, N>;

		/* character type */
		using char_t = T;

		/* const pointer type */
		using const_ptr = const char_t*;

		/* const reference type */
		using const_ref = const char_t(&)[N];

		/* size type */
		using size_type = decltype(N);


		// -- public members ----------------------------------------------

		/* array of characters */
		char_t _data[N];


		// -- public lifecycle --------------------------------------------

		/* deleted default constructor */
		basic_string_literal(void) = delete;

		/* array constructor */
		template <typename U, size_type M>
		consteval basic_string_literal(const U (&str)[M]) noexcept
		: _data{} {
			xns::copy(_data, str);
		}

		/* copy constructor */
		consteval basic_string_literal(const self&) noexcept = default;

		/* move constructor */
		consteval basic_string_literal(self&&) noexcept = default;

		/* destructor */
		~basic_string_literal(void) noexcept = default;


		// -- public assignment operators ---------------------------------

		/* copy assignment operator */
		consteval auto operator=(const self&) noexcept -> self& = default;

		/* move assignment operator */
		consteval auto operator=(self&&) noexcept -> self& = default;


		// -- public accessors --------------------------------------------

		/* data */
		consteval auto data(void) const noexcept -> const_ref {
			return _data;
		}

		/* size */
		consteval auto size(void) const noexcept -> size_type {
			return N - 1; // assume null-terminated
		}


		// -- public conversion operators ---------------------------------

		/* const pointer conversion operator */
		constexpr operator const_ref(void) const noexcept {
			return _data;
		}


		// -- public comparison operators ---------------------------------

		/* equality operator */
		template <typename U, size_type M>
		consteval auto operator==(const basic_string_literal<U, M>& other) const noexcept -> bool {
			return xns::compare(_data, other._data) == 0;
		}

		/* inequality operator */
		template <typename U, size_type M>
		consteval auto operator!=(const basic_string_literal<U, M>& other) const noexcept -> bool {
			return xns::compare(_data, other._data) != 0;
		}

		/* less than operator */
		template <typename U, size_type M>
		consteval auto operator<(const basic_string_literal<U, M>& other) const noexcept -> bool {
			return xns::compare(_data, other._data) < 0;
		}

		/* greater than operator */
		template <typename U, size_type M>
		consteval auto operator>(const basic_string_literal<U, M>& other) const noexcept -> bool {
			return xns::compare(_data, other._data) > 0;
		}

		/* less than or equal to operator */
		template <typename U, size_type M>
		consteval auto operator<=(const basic_string_literal<U, M>& other) const noexcept -> bool {
			return xns::compare(_data, other._data) <= 0;
		}

		/* greater than or equal to operator */
		template <typename U, size_type M>
		consteval auto operator>=(const basic_string_literal<U, M>& other) const noexcept -> bool {
			return xns::compare(_data, other._data) >= 0;
		}

	};


	// -- deduction guides ----------------------------------------------------

	template <typename T, decltype(sizeof(0)) N>
	basic_string_literal(const T (&)[N]) -> basic_string_literal<T, N>;



	/* equality operator */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	inline consteval auto operator==(const xns::basic_string_literal<T1, L>& lhs,
									 const T2 (&rhs)[R]) noexcept -> bool {
		return xns::compare(lhs._data, rhs) == 0;
	}

	/* equality operator (reverse) */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	inline consteval auto operator==(const T1 (&lhs)[L],
									 const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
		return xns::compare(lhs, rhs._data) == 0;
	}

	/* inequality operator */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	inline consteval auto operator!=(const xns::basic_string_literal<T1, L>& lhs,
									 const T2 (&rhs)[R]) noexcept -> bool {
		return xns::compare(lhs._data, rhs) != 0;
	}

	/* inequality operator (reverse) */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	inline constexpr auto operator!=(const T1 (&lhs)[L],
									 const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
		return xns::compare(lhs, rhs._data) != 0;
	}

	/* less than operator */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	inline constexpr auto operator<(const xns::basic_string_literal<T1, L>& lhs,
									const T2 (&rhs)[R]) noexcept -> bool {
		return xns::compare(lhs._data, rhs) < 0;
	}

	/* less than operator (reverse) */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	inline constexpr auto operator<(const T1 (&lhs)[L],
									const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
		return xns::compare(lhs, rhs._data) < 0;
	}

	/* greater than operator */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	inline constexpr auto operator>(const xns::basic_string_literal<T1, L>& lhs,
									const T2 (&rhs)[R]) noexcept -> bool {
		return xns::compare(lhs._data, rhs) > 0;
	}

	/* greater than operator (reverse) */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	inline constexpr auto operator>(const T1 (&lhs)[L],
									const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
		return xns::compare(lhs, rhs._data) > 0;
	}

	/* less than or equal to operator */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	inline constexpr auto operator<=(const xns::basic_string_literal<T1, L>& lhs,
									 const T2 (&rhs)[R]) noexcept -> bool {
		return xns::compare(lhs._data, rhs) <= 0;
	}

	/* less than or equal to operator (reverse) */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	inline constexpr auto operator<=(const T1 (&lhs)[L],
									 const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
		return xns::compare(lhs, rhs._data) <= 0;
	}

	/* greater than or equal to operator */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	inline constexpr auto operator>=(const xns::basic_string_literal<T1, L>& lhs,
									 const T2 (&rhs)[R]) noexcept -> bool {
		return xns::compare(lhs._data, rhs) >= 0;
	}

	/* greater than or equal to operator (reverse) */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	inline constexpr auto operator>=(const T1 (&lhs)[L],
									 const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
		return xns::compare(lhs, rhs._data) >= 0;
	}



} // namespace xns

#endif // XNS_STRING_LITERAL_HEADER
