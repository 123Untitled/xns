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

#ifndef XNS_STRING_UTILS_HEADER
#define XNS_STRING_UTILS_HEADER

#include "type_traits/type_categories/is_char.hpp"
#include "type_traits/types.hpp"
#include "containers/array.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	/* is upper */
	template <xns::is_char T>
	inline constexpr auto is_upper(const T character) noexcept -> bool {
		// return true if character is upper
		return (character & static_cast<T>(0x60)) == static_cast<T>(0x40);
	}

	/* is lower */
	template <xns::is_char T>
	inline constexpr auto is_lower(const T character) noexcept -> bool {
		// return true if character is lower
		return (character & static_cast<T>(0x60)) == static_cast<T>(0x60);
	}

	/* is alpha */
	template <xns::is_char T>
	inline constexpr auto is_alpha(const T character) noexcept -> bool {
		// return true if character is alpha
		return is_uppercase(character) || is_lowercase(character);
	}

	/* is alphanumeric */
	template <xns::is_char T>
	inline constexpr auto is_alnum(const T character) noexcept -> bool {
		// return true if character is alphanumeric
		return is_alpha(character) || is_digit(character);
	}

	/* is punctuation */
	template <xns::is_char T>
	inline constexpr auto is_punct(const T character) noexcept -> bool {
		// return true if character is punctuation
		return ((character > static_cast<T>(0x20) && character < static_cast<T>(0x30))
				|| (character > static_cast<T>(0x39) && character < static_cast<T>(0x41))
				|| (character > static_cast<T>(0x5a) && character < static_cast<T>(0x61))
				|| (character > static_cast<T>(0x7a) && character < static_cast<T>(0x7f)));
	}

	/* is digit */
	template <xns::is_char T>
	inline constexpr auto is_digit(const T character) noexcept -> bool {
		// return true if character is digit
		return (character ^ static_cast<T>(0x30)) < static_cast<T>(0x0a);
	}

	/* is hexadecimal */
	template <xns::is_char T>
	inline constexpr auto is_xdigit(const T character) noexcept -> bool {
		// return true if character is hexadecimal
		return (xns::is_digit(character)
				|| (character > static_cast<T>(0x40) && character < static_cast<T>(0x47))
				|| (character > static_cast<T>(0x60) && character < static_cast<T>(0x67)));
	}

	/* is print */
	template <xns::is_char T>
	inline constexpr auto is_print(const T character) noexcept -> bool {
		// return true if character is printable
		return (character > static_cast<T>(0x1f))
			&& (character < static_cast<T>(0x7f));
	}

	/* is graphical */
	template <xns::is_char T>
	inline constexpr auto is_graph(const T character) noexcept -> bool {
		// return true if character is graphical
		return (character > static_cast<T>(0x20))
			&& (character < static_cast<T>(0x7f));
	}

	/* is space */
	template <xns::is_char T>
	inline constexpr auto is_space(const T character) noexcept -> bool {
		// return true if character is white-space
		return (character == static_cast<T>(0x20))
			|| (character  > static_cast<T>(0x08) && character < static_cast<T>(0x0e));
	}

	/* is blank */
	template <xns::is_char T>
	inline constexpr auto is_blank(const T character) noexcept -> bool {
		// return true if character is blank
		return (character == static_cast<T>(0x09) || character == static_cast<T>(0x20));
	}

	/* is cntrl */
	template <xns::is_char T>
	inline constexpr auto is_cntrl(const T character) noexcept -> bool {
		// return true if character is control
		return character < 0x20 || character == 0x7f;
	}

	/* is multi-byte */
	template <xns::is_char T>
	inline constexpr auto is_multi(const T character) noexcept -> bool {
		// return true if character is multi-byte
		return character & 0x80;
	}

	/* to uppercase */
	template <xns::is_char T>
	inline constexpr auto to_upper(const T character) noexcept -> T {
		// return uppercase character
		return is_lower(character) ? character - 0x20 : character;
	}

	/* to lowercase */
	template <xns::is_char T>
	inline constexpr auto to_lower(const T character) noexcept -> T {
		// return lowercase character
		return is_upper(character) ? character + 0x20 : character;
	}


} // namespace xns

#endif // XNS_STRING_UTILS_HEADER
