#ifndef PAIR_HEADER
#define PAIR_HEADER

// local headers
#include "types.hpp"
#include "move.hpp"
#include "indexed_element.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- P A I R -------------------------------------------------------------

	template <typename T1, typename T2>
	class pair final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = pair<T1, T2>;

			/* first type */
			using first = T1;

			/* second type */
			using second = T2;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline constexpr pair(void)
			: _first{}, _second{} {}

			/* copy pair constructor */
			inline constexpr pair(const first& first, const second& second)
			: _first{first}, _second{second} { }

			/* move pair constructor */
			inline constexpr pair(first&& first, second&& second)
			: _first{xns::move(first)}, _second{xns::move(second)} {}

			/* copy constructor */
			inline constexpr pair(const self& other)
			: _first{other._first}, _second{other._second} {}

			/* move constructor */
			inline constexpr pair(self&& other) noexcept
			: _first{xns::move(other._first)}, _second{xns::move(other._second)} { }

			/* destructor */
			inline constexpr ~pair(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy operator */
			inline constexpr auto operator=(const self& other) -> self& {
				// copy first object
				_first = other._first;
				// copy second object
				_second = other._second;
				// return self reference
				return *this;
			}

			/* move operator */
			inline constexpr auto operator=(self&& other) noexcept -> self& {
				// move first object
				_first = xns::move(other._first);
				// move second object
				_second = xns::move(other._second);
				// return self reference
				return *this;
			}


		private:
		public:

			// -- private members ---------------------------------------------

			/* first */
			first _first;

			/* second */
			second _second;


			// -- friends -----------------------------------------------------

			template <typename A, typename B>
			friend inline constexpr auto get(xns::pair<A, B>&) noexcept -> A&;

			template <typename A, typename B>
			friend inline constexpr auto get(xns::pair<B, A>&) noexcept -> A&;


			template <typename A, typename B>
			friend inline constexpr auto get(const xns::pair<A, B>&) noexcept -> const A&;

			template <typename A, typename B>
			friend inline constexpr auto get(const xns::pair<B, A>&) noexcept -> const A&;


			template <typename A, typename B>
			friend inline constexpr auto get(xns::pair<A, B>&&) noexcept -> A&&;

			template <typename A, typename B>
			friend inline constexpr auto get(xns::pair<B, A>&&) noexcept -> A&&;

			template <typename A, typename B>
			friend inline constexpr auto get(const xns::pair<A, B>&&) noexcept -> const A&&;

			template <typename A, typename B>
			friend inline constexpr auto get(const xns::pair<B, A>&&) noexcept -> const A&&;


			template <xns::size_t I, typename A, typename B>
			friend inline constexpr auto get(xns::pair<A, B>&) noexcept -> xns::indexed_element<I, xns::pair<A, B>>&;

			template <xns::size_t I, typename A, typename B>
			friend inline constexpr auto get(const xns::pair<A, B>&) noexcept -> const xns::indexed_element<I, xns::pair<A, B>>&;

			template < xns::size_t I, typename A, typename B>
			friend inline constexpr auto get(xns::pair<A, B>&&) noexcept -> xns::indexed_element<I, xns::pair<A, B>>&&;

			template < xns::size_t I, typename A, typename B>
			friend inline constexpr auto get(const xns::pair<A, B>&&) noexcept -> const xns::indexed_element<I, xns::pair<A, B>>&&;

	};


	template <typename T, typename U>
	inline constexpr auto get(xns::pair<T, U>& pair) noexcept -> T& {
		return pair._first;
	}

	template <typename T, typename U>
	inline constexpr auto get(xns::pair<U, T>& pair) noexcept -> T& {
		return pair._second;
	}


	template <typename T, typename U>
	inline constexpr auto get(const xns::pair<T, U>& pair) noexcept -> const T& {
		return pair._first;
	}

	template <typename T, typename U>
	inline constexpr auto get(const xns::pair<U, T>& pair) noexcept -> const T& {
		return pair._second;
	}


	template <typename T, typename U>
	inline constexpr auto get(xns::pair<T, U>&& pair) noexcept -> T&& {
		return xns::move(pair._first);
	}

	template <typename T, typename U>
	inline constexpr auto get(xns::pair<U, T>&& pair) noexcept -> T&& {
		return xns::move(pair._second);
	}


	template <typename T, typename U>
	inline constexpr auto get(const xns::pair<T, U>&& pair) noexcept -> const T&& {
		return xns::move(pair._first);
	}

	template <typename T, typename U>
	inline constexpr auto get(const xns::pair<U, T>&& pair) noexcept -> const T&& {
		return xns::move(pair._second);
	}





	template <xns::size_t I, typename T1, typename T2>
    inline constexpr auto get(xns::pair<T1, T2>& pair) noexcept -> xns::indexed_element<I, xns::pair<T1, T2>>& {
		// check index
		static_assert(I < 2, "): PAIR: INDEX OUT OF BOUNDS! :(");
		if constexpr (I == 0) {
			return pair._first;
		} else { return pair._second; }
	}

	template <xns::size_t I, typename T1, typename T2>
    inline constexpr auto get(const xns::pair<T1, T2>& pair) noexcept -> const xns::indexed_element<I, xns::pair<T1, T2>>& {
		// check index
		static_assert(I < 2, "): PAIR: INDEX OUT OF BOUNDS! :(");
		if constexpr (I == 0) {
			return pair._first;
		} else { return pair._second; }
	}

	template < xns::size_t I, typename T1, typename T2>
    inline constexpr auto get(xns::pair<T1, T2>&& pair) noexcept -> xns::indexed_element<I, xns::pair<T1, T2>>&& {
		// check index
		static_assert(I < 2, "): PAIR: INDEX OUT OF BOUNDS! :(");
		if constexpr (I == 0) {
			return pair._first;
		} else { return pair._second; }
	}

	template < xns::size_t I, typename T1, typename T2>
    inline constexpr auto get(const xns::pair<T1, T2>&& pair) noexcept -> const xns::indexed_element<I, xns::pair<T1, T2>>&& {
		// check index
		static_assert(I < 2, "): PAIR: INDEX OUT OF BOUNDS! :(");
		if constexpr (I == 0) {
			return pair._first;
		} else { return pair._second; }
	}



}

#endif
