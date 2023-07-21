#ifndef PARAMETER_PACK_HEADER
#define PARAMETER_PACK_HEADER

#include <type_traits>
#include "pack_type.hpp"
#include "integer_sequence.hpp"

// not RENAMED !!!

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	template <class RType, size_t Ip, size_t Ij, class... A>
	struct Get_impl {

		static RType& dispatch(A...);
	};

	template <class RType,  size_t IDX, size_t Jp, class Head, class... A>
	struct Get_impl<RType, IDX, Jp, Head, A...> {

		static RType& dispatch(Head&, A&... args) {
			return Get_impl<RType, IDX, Jp + 1, A...>::dispatch(args...);
		}

	};

	template <size_t IDX, class Head, class... A>
	struct Get_impl<Head, IDX, IDX, Head, A...> {

		static Head& dispatch(Head& head, A&...) {
			return head;
		}

	};


	template <size_t IDX, class... A>
	auto get(A&... args) -> xns::pack_type<IDX, A&...>& {

		return Get_impl<pack_type<IDX, A...>, // type at index
						IDX,                   // index
						0,                   // index J
						A...                 // pack types
						>::dispatch(args...); // pack values

	}



	template <class RType, xns::size_t... INDX, class... A>
	RType pack_extract_imp(xns::index_seq<INDX...>i, A&... args) {
		//debug_sequence(i); // REMOVE i
		//return RType{};
		// extract the pack recursively
		return RType{get<INDX>(args...)...}; //TADA
	}

	template <class RType, xns::size_t BEGIN, xns::size_t END, class... A>
	RType pack_extract(A&... args) {
		// create index range
		xns::make_index_range<BEGIN, END> indxs; // ???
		// call implementation to extract the pack
		return pack_extract_imp<RType>(indxs, args...);
	}





}



#endif
