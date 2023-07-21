#ifndef PACK_TYPE_HEADER
#define PACK_TYPE_HEADER

#include "types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- P A C K T Y P E -----------------------------------------------------

	template <xns::size_t IDX, class... A>
	class _pack_type final {

		// -- A S S E R T I O N S ---------------------------------------------

		/* check if pack is not empty */
		static_assert(sizeof...(A) > 0, "WTF DUDE, THE PACK IS EMPTY!");

		/* check if index is valid */
		static_assert(IDX < sizeof...(A), "INDEX OUT OF RANGE DUDE! STOP DRUGS!");


		private:

			// -- C O N S T A N T S -------------------------------------------

			/* size */
			static constexpr xns::size_t _size = sizeof...(A);


			// -- I M P L E M E N T A T I O N ---------------------------------

			/* forward declaration */
			template <size_t N, class... T>
			struct impl;

			/* case N == IDX */
			template <size_t N, class U, class... T> requires (N == IDX)
			struct impl<N, U, T...> {
				using Type = U;
			};

			/* case N != IDX */
			template <size_t N, class U, class... T> requires (N < IDX)
			struct impl<N, U, T...> {
				using Type = typename impl<N + 1, T...>::Type;
			};


		public:

			// -- T Y P E S ---------------------------------------------------

			/* type of the element at index IDX */
			using Type = typename impl<0, A...>::Type;


			// -- A C C E S S O R S -------------------------------------------

			/* size accessor */
			static inline constexpr xns::size_t size(void) noexcept {
				return _size;
			}

	};

	/* helper alias */
	template <xns::size_t IDX, class... A>
	using pack_type = typename _pack_type<IDX, A...>::Type;

}




#endif
