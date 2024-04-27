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

#ifndef XNS_SPLIT_HEADER
#define XNS_SPLIT_HEADER

// local headers
#include "xns/string/string.hpp"
#include "xns/containers/vector.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {



	/* is charset */
	template <typename ___type>
	bool is_charset(const ___type ch, const ___type* charset) {
		// check if charset is null
		if (!charset) { return false; }
		// loop through charset
		while (*charset) {
			// check if character is in charset
			if (ch == *(charset)++) {
				return true; }
		} return false;
	}


	// re-implement with size check, to avoid null pointer dereference

	/* split */
	template <typename ___type, bool keep = false> requires(keep == false)
	auto split(const xns::basic_string<___type>& str,
			   const xns::basic_string<___type>& sep) -> xns::vector<xns::basic_string<___type>> {

		// check if string is not null
		if (str.empty())
			return {};

		using size_type = typename xns::basic_string<___type>::size_type;
		xns::vector<xns::basic_string<___type>> vec;

		const ___type* ptr = str.data();

		// loop through string characters
		for (size_type z = 0, x = 0; ptr[x]; x += z, z = 0) {
			// skip separator characters
			while (is_charset(ptr[x], sep.data())) { ++x; }
			// count non-separator characters
			while (ptr[x + z]
					&& !is_charset(ptr[x + z], sep.data())) { ++z; }
			// emplace string if z is not zero
			if (z) { vec.emplace_back(&(ptr[x]), z); }
		} // return the vector

		return vec;
	}

			/* divide */ // INFO: split but keep separators
			//template <bool keep = false> requires(keep == true)
			//auto split(self&& sep) const -> xns::vector<self> {
			//	// vector of strings
			//	xns::vector<self> vec;
			//
			//	if (_data) {
			//		size_type z, x = 0;
			//		// loop through string characters
			//		while (_data[x]) {
			//			z = 0;
			//			// count separator characters
			//			while (is_charset(_data[x + z], sep._data)) { ++z; }
			//			// emplace string if z is not zero
			//			if (z) { vec.emplace_back(&(_data[x]), z);
			//				x += z;
			//			}
			//			z = 0;
			//			// count non-separator characters
			//			while (_data[x + z] && !is_charset(_data[x + z], sep._data)) { ++z; }
			//			// emplace string if z is not zero
			//			if (z) { vec.emplace_back(&(_data[x]), z);
			//				x += z;
			//			}
			//		} // return the vector
			//	} return vec;
			//}



			// -- public modifiers --------------------------------------------

			/* to upper */
			//constexpr auto to_upper(void) noexcept -> void {
			//	for (size_type i = 0; i < _size; ++i)
			//		_data[i] = xns::to_upper(_data[i]);
			//}
			//
			///* to lower */
			//constexpr auto to_lower(void) noexcept -> void {
			//	for (size_type i = 0; i < _size; ++i)
			//		_data[i] = xns::to_lower(_data[i]);
			//}
			//

			/* filter */ // INFO: ref functor
			//template <bool inverse = true>
			//auto filter(bool (&is_type)(const value_type)) -> void {
			//	// exit if string is null
			//	if (_data == nullptr) { return; }
			//	// offset
			//	size_type offset = 0;
			//	// loop through string
			//	for (size_type x = 0; x < _size; ++x) {
			//		// check if character is not of type
			//		if (is_type(_data[x]) != inverse) { ++offset; }
			//		// shift characters
			//		else { _data[x - offset] = _data[x]; }
			//	}
			//	_size -= offset;
			//	_data[_size] = 0;
			//}
			//
			//void pull_repeat(void) {
			//	//size_type x = 0;
			//	//size_type z = 0;
			//
			//	//if (_data) {
			//	//	while (z + x < _size) {
			//	//		while (_data[z + x] == _data[z + x + 1])
			//	//			x++;
			//	//		_data[z] = _data[z + x];
			//	//		z++;
			//	//	} _size = z;
			//	//	_data[_size] = nullchar;
			//	//}
			//}
			//
			///* forward remove duplicates */
			//void forward_remove_duplicates(void) {
			//	static_assert(sizeof(value_type) == 1, "value_type must be 8-bit");
			//
			//	bool seen[UINT8_MAX] = { false };
			//
			//	if (!_data) { return; }
			//
			//	xns::u8* ptr = reinterpret_cast<xns::u8*>(_data);
			//	// initialize new size
			//	size_type length = _size;
			//
			//	_size = 0;
			//	// loop through string characters
			//	for (size_type z = 0, x = 0; x < length; ++x) {
			//		// check if character has been seen
			//		if (seen[ptr[x]]) { continue; }
			//		// set character as seen
			//		seen[ptr[x]] = true;
			//		// copy character to new position
			//		_data[_size++] = _data[x];
			//	} // set null character
			//	_data[_size] = 0;
			//
			//}
			//
			///* backward remove duplicates */
			//void backward_remove_duplicates(void) {
			//
			//	//bool seen[UINT8_MAX] = { false };
			//
			//	//if (!_data) { return; }
			//
			//	//UInt8* ptr = reinterpret_cast<UInt8*>(_data);
			//
			//	//size_type x = _size;
			//	//size_type z = x;
			//
			//	//while (x--) {
			//	//	if (seen[ptr[x]]) { continue; }
			//	//	seen[ptr[x]] = true;
			//	//	_data[--z] = _data[x];
			//	//}
			//	//_size = _size - z;
			//
			//	//for (x = 0; x < _size; ++x) {
			//	//	_data[x] = _data[x + z];
			//	//} _data[_size] = 0;
			//
			//}
			//
			//
			//// -- S E A R C H I N G -------------------------------------------
			//
			///* next word */
			//size_type next_word(const size_type index) const {
			//	// idle if nullptr or index exceed length
			//	if (_data != nullptr && index < _size) {
			//
			//		size_type x = index;
			//		// skip printable characters
			//		while (xns::is_print(_data[x])) { ++x; }
			//		// skip whitespace characters
			//		while (xns::is_space(_data[x])) { ++x; }
			//
			//		// check null character
			//		if (_data[x]) { return x; }
			//
			//	} // else return unchanged index
			//	return index;
			//}
			//
			///* previous word */ // INFO: not well implemented
			//size_type previous_word(const size_type index) const {
			//	// idle if nullptr or index exceed length
			//	if (_data != nullptr && index < _size) {
			//
			//		size_type x = index;
			//		// skip whitespace characters
			//		while (x != 0 && xns::is_space(_data[x])) { --x; }
			//		// skip printable characters
			//		while (x != 0 && xns::is_alpha(_data[x])) { --x; }
			//
			//		return x;
			//	}
			//	return index;
			//}
			//
			///* next character */
			//size_type next_character(const size_type index, const value_type character) const {
			//	// idle if nullptr or index exceed length
			//	if (_data != nullptr && index < _size) {
			//		// loop through string
			//		for (size_type x = index; x < _size; ++x) {
			//			// return index if character is found
			//			if (_data[x] == character) { return x; }
			//		}
			//	} // else return unchanged index
			//	return index;
			//}
			//
			///* previous character */
			//size_type previous_character(const size_type index, const value_type character) const {
			//	// idle if nullptr or index exceed length
			//	if (_data != nullptr && index < _size) {
			//		// loop through string
			//		for (size_type x = index; x != 0; --x) {
			//			// return index if character is found
			//			if (_data[x] == character) return x;
			//		}
			//	} // else return unchanged index
			//	return index;
			//}
			//
			///* is only */
			//bool is_only(bool (&is_type)(const value_type)) const {
			//	// return false if string is null or empty
			//	if (!_data || !_size) { return false; } // WARNING: functor is not checked
			//	// loop through string
			//	for (size_type x = 0; x < _size; ++x) {
			//		// return false if character is not of type
			//		if (!is_type(_data[x])) { return false; }
			//	} // return true if all characters are of type
			//	return true;
			//}




}

#endif // XNS_SPLIT_HPP
