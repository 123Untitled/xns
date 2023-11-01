#ifndef XNS_SORT_HPP
#define XNS_SORT_HPP

#include "vector.hpp"
#include <algorithm>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {



	// non-recursive quicksort
	template <typename T>
	auto quicksort(xns::vector<T>& vec, xns::size_t low, xns::size_t hi) -> void {
	}




	template <typename T>
	auto sort(xns::vector<T>& vec) -> void {
		std::sort(vec.begin(), vec.end());
	}


}

#endif // XNS_SORT_HPP
