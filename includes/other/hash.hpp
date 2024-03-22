#ifndef XNS_HASH_HEADER
#define XNS_HASH_HEADER

// local headers
#include "type_traits/types.hpp"
#include "string/string.hpp"
#include "type_traits/type_modifications/make_unsigned.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	template <typename T>
	auto hash(const T& value) noexcept -> xns::u64 {

		enum : xns::u64 {
			OFFSET_BASIS = 14695981039346656037u,
				   PRIME = 1099511628211u
		};

		xns::u64 hash{OFFSET_BASIS};

		if constexpr (xns::is_string<T>) {
			for (xns::string::size_type i = 0; i < value.size(); ++i) {
				hash ^= static_cast<xns::make_unsigned<typename T::char_t>>(value[i]);
				hash *= PRIME;
			}
		}
		else {

			const xns::ubyte* ptr = reinterpret_cast<const xns::ubyte*>(&value);

			for (xns::size_t i = 0; i < sizeof(T); ++i) {
				hash ^= static_cast<xns::u64>(ptr[i]);
				hash *= PRIME;
			}
		}

		return hash;
	}



}

#endif // HASH_HEADER


// MurmurHash3 was written by Austin Appleby, and is placed in the public
