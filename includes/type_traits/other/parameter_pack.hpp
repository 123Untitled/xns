#ifndef XNS_PARAMETER_PACK_HEADER
#define XNS_PARAMETER_PACK_HEADER

#include <type_traits>
#include "type_at.hpp"
#include "integer_sequence.hpp"

#include "is_constructible.hpp"

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
	auto _get(A&... args) -> xns::type_at<IDX, A&...>& {

		return Get_impl<type_at<IDX, A...>, // type at index
						IDX,                   // index
						0,                   // index J
						A...                 // pack types
						>::dispatch(args...); // pack values

	}



	template <typename R, xns::size_t... IDX, typename... A>
	auto pack_extract_imp(xns::index_sequence<IDX...>i, A&... args) -> R {
		//debug_sequence(i); // REMOVE i
		//return RType{};
		// extract the pack recursively
		return R{_get<IDX>(args...)...}; //TADA
	}

	template <typename R, xns::size_t BEGIN, xns::size_t END, typename... A>
	auto pack_extract(A&... args) -> R {
		// create index range
		xns::make_index_range<BEGIN, END> indxs; // ???
		// call implementation to extract the pack
		return pack_extract_imp<R>(indxs, args...);
	}


	template <class... A>
	struct constructible_type {


		private:

			// -- private structs ---------------------------------------------

			template <class...>
			struct impl;

			template <class T, class... Tp>
			requires (xns::is_constructible_strict<T, A...> == false)
			struct impl<T, Tp...> final {
				using type = typename impl<Tp...>::type;
			};

			template <class T, class... Tp>
			requires (xns::is_constructible_strict<T, A...> == true)
			struct impl<T, Tp...> final {
				using type = T;
			};

			template <class T> requires (!xns::is_constructible_strict<T, A...>)
			struct impl<T> final {
				static_assert(xns::is_constructible_strict<T, A...>,
							  "): NO CONSTRUCTIBLE TYPE IN VARIADIC :(");
			};



		public:

			template <class... T>
			static consteval auto counter(void) -> xns::size_t {
				xns::size_t count = 0;
				((count += xns::is_constructible_strict<T, A...>), ...);
				return count;
			}


			template <class... T>
			using type = typename impl<T...>::type;
	};









}



#endif
