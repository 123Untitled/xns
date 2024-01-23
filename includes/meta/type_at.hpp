#ifndef XNS_TYPE_AT_HEADER
#define XNS_TYPE_AT_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- T Y P E  A T --------------------------------------------------------

	namespace impl {


		template <decltype(sizeof(0)) I, typename... A>
		class type_at final {


			// -- assertions --------------------------------------------------

			/* check if pack is not empty */
			static_assert(sizeof...(A) > 0, "[xns::type_at] Parameter pack is empty.");

			/* check if index is valid */
			static_assert(I < sizeof...(A), "[xns::type_at] Index is out of range.");


			private:

				// -- private implementation ----------------------------------

				/* forward declaration */
				template <decltype(I) N, typename... T>
				struct impl;

				/* specialization for N == IDX */
				template <decltype(I) N, typename U, typename... T> requires (N == I)
				struct impl<N, U, T...> {
					using type = U;
				};

				/* specialization for N < IDX */
				template <decltype(I) N, typename U, typename... T> requires (N < I)
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
	template <decltype(sizeof(0)) I, class... A>
	using type_at = typename impl::type_at<I, A...>::type;

}




#endif
