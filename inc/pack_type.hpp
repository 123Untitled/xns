#ifndef PACK_TYPE_HEADER
#define PACK_TYPE_HEADER

#include <type_traits>

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- P A C K T Y P E -----------------------------------------------------

	template <size_t IDX, class... A>
	class PackType final {

		private:

			/* check if pack is not empty */
			static_assert(sizeof...(A) > 0, "WTF DUDE, THE PACK IS EMPTY!");

			/* check if index is valid */
			static_assert(IDX < sizeof...(A), "INDEX OUT OF RANGE DUDE! STOP DRUGS!");

			/* size */
			static constexpr size_t SIZE = sizeof...(A);


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

			/* type of the element at index IDX */
			using Type = typename impl<0, A...>::Type;

			/* size accessor */
			static inline constexpr size_t size(void) noexcept {
				return SIZE;
			}

	};

	/* alias to PackType type */
	template <size_t IDX, class... A>
	using PackType_t = typename PackType<IDX, A...>::Type;

}




#endif
