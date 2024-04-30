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

#include "xns/type_traits/types.hpp"
#include "xns/type_traits/type_categories/is_char.hpp"
#include "xns/type_traits/relationships_and_property_queries/is_comparable.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- C O P Y -------------------------------------------------------------

	namespace ___impl {

		/* copy implementation */
		template <typename T, decltype(sizeof(0)) D, decltype(D) S, decltype(S) I>
		constexpr auto ___copy(T (&dst)[D], const T (&src)[S]) noexcept -> void {
			if constexpr (I == D or I == S){
				return;
			} else {
				dst[I] = src[I];
				xns::___impl::___copy<T, D, S, I + 1>(dst, src);
			}
		}

	}

	/* copy */
	template <typename ___type, xns::size_t ___ds, xns::size_t ___ss>
	constexpr auto copy(___type (&___dst)[___ds], const ___type (&___src)[___ss]) noexcept -> void {
		xns::___impl::___copy<___type, ___ds, ___ss, 0U>(___dst, ___src);
	}


	// -- C O M P A R E -------------------------------------------------------


	namespace ___impl {

		/* compare implementation */
		template <typename T1, typename T2, decltype(sizeof(0)) S, decltype(S) I>
		constexpr auto ___compare(const T1 (&lhs)[S], const T2 (&rhs)[S]) noexcept -> signed int {
			if constexpr (I == S) {
				return 0;
			} else {
				return (lhs[I] == rhs[I])
					 ? (xns::___impl::___compare<T1, T2, S, I + 1>(lhs, rhs))
					 : (lhs[I] > rhs[I] ? +1 : -1);
			}
		}

	}

	/* compare */
	template <typename T1, typename T2, decltype(sizeof(0)) L, decltype(L) R>
	constexpr auto compare(const T1 (&lhs)[L], const T2 (&rhs)[R]) noexcept -> signed int {

		// assert that type is comparable
		static_assert(xns::is_comparable<T1, T2>, "Template parameter 'T' must be a comparable type.");

		// check for equal size
		if constexpr (L == R)
			return xns::___impl::___compare<T1, T2, L, 0U>(lhs, rhs);
		else
			return (L > R ? +1U : -1U);
	}



	// -- B A S I C  S T R I N G  L I T E R A L -------------------------------

	template <typename ___type, xns::size_t ___size>
	struct basic_string_literal final {


		// -- assertions ------------------------------------------------------

		/* check character type */
		static_assert(xns::is_char<___type>,
				"basic_string_literal: template parameter '___type' must be a character type.");

		/* check for null size */
		static_assert(___size > 0U,
				"basic_string_literal: template parameter '___size' must be greater than zero.");


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = xns::basic_string_literal<___type, ___size>;


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type = ___type;

			/* const reference type */
			using const_reference = const value_type(&)[___size];

			/* size type */
			using size_type = decltype(___size);


			// -- public members ----------------------------------------------

			/* data */
			value_type _data[___size];


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			basic_string_literal(void) = delete;

			/* array constructor */
			template <typename ___tp, size_type ___sz>
			consteval basic_string_literal(const ___tp (&___str)[___sz]) noexcept
			: _data{} {
				xns::copy(_data, ___str);
			}


			/* copy constructor */
			consteval basic_string_literal(const ___self&) noexcept = default;

			/* move constructor */
			consteval basic_string_literal(___self&&) noexcept = default;

			/* destructor */
			constexpr ~basic_string_literal(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			consteval auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			consteval auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* data */
			consteval auto data(void) const noexcept -> const_reference {
				return _data;
			}

			/* size */
			consteval auto size(void) const noexcept -> size_type {
				return ___size - 1U; // assume null-terminated
			}


			// -- public conversion operators ---------------------------------

			/* const reference conversion operator */
			constexpr operator const_reference(void) const noexcept {
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

	template <typename ___type, decltype(sizeof(0)) ___size>
	basic_string_literal(const ___type (&)[___size]) -> basic_string_literal<___type, ___size>;



	/* equality operator */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	consteval auto operator==(const xns::basic_string_literal<T1, L>& lhs,
									 const T2 (&rhs)[R]) noexcept -> bool {
		return xns::compare(lhs._data, rhs) == 0;
	}

	/* equality operator (reverse) */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	consteval auto operator==(const T1 (&lhs)[L],
									 const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
		return xns::compare(lhs, rhs._data) == 0;
	}

	/* inequality operator */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	consteval auto operator!=(const xns::basic_string_literal<T1, L>& lhs,
									 const T2 (&rhs)[R]) noexcept -> bool {
		return xns::compare(lhs._data, rhs) != 0;
	}

	/* inequality operator (reverse) */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	constexpr auto operator!=(const T1 (&lhs)[L],
									 const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
		return xns::compare(lhs, rhs._data) != 0;
	}

	/* less than operator */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	constexpr auto operator<(const xns::basic_string_literal<T1, L>& lhs,
									const T2 (&rhs)[R]) noexcept -> bool {
		return xns::compare(lhs._data, rhs) < 0;
	}

	/* less than operator (reverse) */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	constexpr auto operator<(const T1 (&lhs)[L],
									const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
		return xns::compare(lhs, rhs._data) < 0;
	}

	/* greater than operator */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	constexpr auto operator>(const xns::basic_string_literal<T1, L>& lhs,
									const T2 (&rhs)[R]) noexcept -> bool {
		return xns::compare(lhs._data, rhs) > 0;
	}

	/* greater than operator (reverse) */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	constexpr auto operator>(const T1 (&lhs)[L],
									const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
		return xns::compare(lhs, rhs._data) > 0;
	}

	/* less than or equal to operator */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	constexpr auto operator<=(const xns::basic_string_literal<T1, L>& lhs,
									 const T2 (&rhs)[R]) noexcept -> bool {
		return xns::compare(lhs._data, rhs) <= 0;
	}

	/* less than or equal to operator (reverse) */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	constexpr auto operator<=(const T1 (&lhs)[L],
									 const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
		return xns::compare(lhs, rhs._data) <= 0;
	}

	/* greater than or equal to operator */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	constexpr auto operator>=(const xns::basic_string_literal<T1, L>& lhs,
									 const T2 (&rhs)[R]) noexcept -> bool {
		return xns::compare(lhs._data, rhs) >= 0;
	}

	/* greater than or equal to operator (reverse) */
	template <typename T1, typename T2,
			  decltype(sizeof(0)) L, decltype(L) R>
	constexpr auto operator>=(const T1 (&lhs)[L],
									 const xns::basic_string_literal<T2, R>& rhs) noexcept -> bool {
		return xns::compare(lhs, rhs._data) >= 0;
	}



} // namespace xns

#endif // XNS_STRING_LITERAL_HEADER
