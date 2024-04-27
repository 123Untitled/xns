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

#ifndef XNS_CHAR_TRAITS_HEADER
#define XNS_CHAR_TRAITS_HEADER


#include "xns/type_traits/type_categories/is_char.hpp"
#include "xns/type_traits/type_modifications/make_unsigned.hpp"

#include "xns/type_traits/types.hpp"
#include "xns/config/config.hpp"
#include "xns/config/macros.hpp"



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- C H A R  T R A I T S ------------------------------------------------

	/* char specialization */
	template <typename ___type>
	struct char_traits final {


		// -- assertions ------------------------------------------------------

		/* check if ___type is char type */
		static_assert(xns::is_char<___type>,
				"char_traits: ___type must be char type");


		// -- types -----------------------------------------------------------

		/* self type */
		using self            = xns::char_traits<___type>;

		/* char type */
		using char_type       = ___type;

		/* pointer type */
		using pointer         = char_type*;

		/* const pointer type */
		using const_pointer   = const char_type*;

		/* reference type */
		using reference       = char_type&;

		/* const reference type */
		using const_reference = const char_type&;

		/* size type */
		using size_type       = xns::size_t;


		// -- lifecycle -------------------------------------------------------

		/* non-instantiable struct */
		___xns_not_instantiable(char_traits);


		// -- static methods --------------------------------------------------

		/* assign */
		static constexpr auto assign(reference ___lhs, const_reference ___rhs) noexcept -> void {
			___lhs = ___rhs;
		}

		/* fill */
		static constexpr auto fill(pointer ___st, const size_type ___sz, const_reference ___ch) noexcept -> void {
			for (size_type i = 0U; i < ___sz; ++i)
				___st[i] = ___ch;
		}

		/* equal */
		static constexpr auto equal(const_reference ___c1, const_reference ___c2) noexcept -> bool {
			return ___c1 == ___c2;
		}

		/* lower */
		static constexpr auto lower(const_reference ___c1, const_reference ___c2) noexcept -> bool {
			return static_cast<xns::make_unsigned<char_type>>(___c1)
				 < static_cast<xns::make_unsigned<char_type>>(___c2);
		}

		/* compare */
		static constexpr auto compare(const_pointer ___lhs, const_pointer ___rhs, const size_type ___sz) noexcept -> int {
			for (size_type i = 0U; i < ___sz; ++i) {
				if (___lhs[i] != ___rhs[i])
					return ___lhs[i] > ___rhs[i] ? 1 : -1;
			} return 0;
		}

		/* compare */
		static constexpr auto compare(const_pointer ___lhs, const_pointer ___rhs) noexcept -> int {
			for (size_type i = 0U; ___lhs[i] != static_cast<char_type>(0) || ___rhs[i] != static_cast<char_type>(0); ++i) {
				if (___lhs[i] != ___rhs[i])
					return ___lhs[i] > ___rhs[i] ? 1 : -1;
			} return 0;
		}

		/* length */
		static constexpr auto length(const_pointer ___st) noexcept -> size_type {
			size_type ___len = 0U;
			for (; ___st[___len] != static_cast<char_type>(0); ++___len);
			return ___len;
		}

		/* find */
		static constexpr auto find(const_pointer ___st, const size_type ___sz, const char_type ___ch) noexcept -> const_pointer {
			for (size_type i = 0U; i < ___sz; ++i) {
				if (___st[i] == ___ch)
					return ___st + i;
			} return nullptr;
		}

		/* copy */
		static constexpr auto copy(pointer ___s1, const_pointer ___s2, const size_type ___sz) noexcept -> void {
			for (size_type i = 0U; i < ___sz; ++i)
				___s1[i] = ___s2[i];
		}

		/* move */
		static constexpr auto move(pointer ___dst, const_pointer ___src, const size_type ___sz) noexcept -> void {
			if (___dst < ___src)
				for (size_type i = 0U; i < ___sz; ++i)
					___dst[i] = ___src[i];
			else
				for (size_type i = ___sz; i > 0U; --i)
					___dst[i - 1U] = ___src[i - 1U];
		}

	}; // struct char_traits

} // namespace xns

#endif // XNS_CHAR_TRAITS_HEADER
