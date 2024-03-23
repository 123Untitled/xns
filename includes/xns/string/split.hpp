#ifndef XNS_SPLIT_HPP
#define XNS_SPLIT_HPP

// local headers
#include "xns/string.hpp"
#include "xns/vector.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	/* split */
	template <typename T, bool keep = false> requires(keep == false)
	auto split(const xns::basic_string<T>& str,
			   const xns::basic_string<T>& sep) -> xns::vector<xns::basic_string<T>> {

		// check if string is not null
		if (str.empty())
			return {};

		using size_type = typename xns::basic_string<T>::size_type;
		xns::vector<xns::basic_string<T>> vec;

		const T* ptr = str.data();

		// loop through string characters
		for (size_type z = 0, x = 0; ptr[x]; x += z, z = 0) {
			// skip separator characters
			while (is_charset(ptr[x], sep.data())) { ++x; }
			// count non-separator characters
			while (ptr[x + z]
					&& !is_charset(ptr[x + z], sep._str)) { ++z; }
			// emplace string if z is not zero
			if (z) { vec.emplace_back(&(ptr[x]), z); }
		} // return the vector

		return vec;
	}






}

#endif // XNS_SPLIT_HPP
