#ifndef PACK_TYPE_HEADER
#define PACK_TYPE_HEADER

#include "types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- T Y P E  A T --------------------------------------------------------

	namespace impl {


		template <xns::size_t IDX, typename... A>
		class type_at final {


			// -- assertions --------------------------------------------------

			/* check if pack is not empty */
			static_assert(sizeof...(A) > 0, "TYPE_AT: EMPTY PACK!");

			/* check if index is valid */
			static_assert(IDX < sizeof...(A), "TYPE_AT: INDEX OUT OF RANGE!");


			private:

				// -- private implementation ----------------------------------

				/* forward declaration */
				template <decltype(IDX) N, typename... T>
				struct impl;

				/* specialization for N == IDX */
				template <decltype(IDX) N, typename U, typename... T> requires (N == IDX)
				struct impl<N, U, T...> {
					using type = U;
				};

				/* specialization for N < IDX */
				template <decltype(IDX) N, typename U, typename... T> requires (N < IDX)
				struct impl<N, U, T...> {
					using type = typename impl<N + 1, T...>::type;
				};


			public:

				// -- public types --------------------------------------------

				/* type indexed by IDX */
				using type = typename impl<0, A...>::type;


		};

	}

	/* type at type */
	template <xns::size_t IDX, class... A>
	using type_at = typename impl::type_at<IDX, A...>::type;

}




#endif
