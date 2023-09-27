#ifndef RECT_HEADER
#define RECT_HEADER

#include <iostream>

#include "types.hpp"
#include "array.hpp"
#include "is_arithmetic.hpp"


#define PRECT(rect) std::cout << "Rect(" << rect.x << ", " << rect.y << ", " << rect.w << ", " << rect.h << ")" << std::endl;


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E C T  S T R U C T ------------------------------------------------

	template <typename P, typename D = P>
	struct rect final {


		// -- assertions ------------------------------------------------------

		/* check P and D are arithmetic types */
		static_assert(xns::is_arithmetic<P>
					&& xns::is_arithmetic<D>, "): RECT: P AND D MUST BE ARITHMETIC TYPES :(");


		// -- types -----------------------------------------------------------

		/* self type */
		using self = rect<P, D>;

		/* position type */
		using pos = P;

		/* dimension type */
		using dim = D;


		// -- members ---------------------------------------------------------

		/* position */
		pos x, y;

		/* dimension */
		dim w, h;


		// -- constructors ----------------------------------------------------

		/* default constructor */
		inline constexpr rect(void) noexcept
		: x{0}, y{0}, w{0}, h{0} {}

		/* size and position constructor */
		inline constexpr rect(const pos x,
							  const pos y,
							  const dim w,
							  const dim h) noexcept
		: x{x}, y{y}, w{w}, h{h} {}

		/* copy constructor */
		inline constexpr rect(const self& other) noexcept
		: x{other.x}, y{other.y}, w{other.w}, h{other.h} {}

		/* move constructor */
		inline constexpr rect(self&& other) noexcept
		: rect{other} {}

		/* destructor */
		~rect(void) noexcept = default;


		// -- assignment operators --------------------------------------------

		/* copy assignment operator */
		inline constexpr auto operator=(const self& other) noexcept -> self& {
			// copy dimension
			w = other.w; h = other.h;
			// copy position
			x = other.x; y = other.y;
			// return self reference
			return *this;
		}

		/* move assignment operator */
		inline constexpr auto operator=(self&& other) noexcept -> self& {
			// call copy assignment
			return operator=(other);
		}


		// -- boolean operators -----------------------------------------------

		/* bool operator */
		inline constexpr explicit operator bool(void) const noexcept {
			// check if empty
			return !empty();
		}

		/* bool not operator */
		inline constexpr auto operator!(void) const noexcept -> bool {
			// check if empty
			return empty();
		}


		// -- comparison operators --------------------------------------------

		/* equality operator */
		inline constexpr auto operator==(const self& other) const noexcept -> bool {
			// return equality
			return w == other.w && h == other.h;
		}

		/* inequality operator */
		inline constexpr auto operator!=(const self& other) const noexcept -> bool {
			// return inequality
			return !operator==(other);
		}

		/* less than operator */
		inline constexpr auto operator<(const self& other) const noexcept -> bool {
			// return less than
			return w * h < other.w * other.h;
		}

		/* less than or equal operator */
		inline constexpr auto operator<=(const self& other) const noexcept -> bool {
			// return less than or equal
			return *this < other || *this == other;
		}

		/* greater than operator */
		inline constexpr auto operator>(const self& other) const noexcept -> bool {
			// return greater than
			return !operator<=(other);
		}

		/* greater than or equal operator */
		inline constexpr auto operator>=(const self& other) const noexcept -> bool {
			// return greater than or equal
			return !operator<(other);
		}


		// -- accessors -------------------------------------------------------

		/* empty */
		inline constexpr auto empty(void) const noexcept -> bool {
			// check if empty
			return w == 0 || h == 0;
		}


	};


	// -- R E C T  F U N C T I O N S ------------------------------------------

	template <auto N, typename P, typename D>
	constexpr auto horizontal_split(const xns::rect<P, D>& rect) noexcept -> xns::array<xns::rect<P, D>, N> {

		// check N is not zero
		static_assert(N > 0, "): HORITZONTAL_SPLIT: DIVISION BY ZERO ? GO IN HELL :(");

		// check N

		D width = rect.w / N;
		D rest = rect.w % N;


		xns::array<xns::rect<P, D>, N> rects;

		for (decltype(N) i = 0; i < N; ++i) {
			rects[i].x = rect.x + (i * width);
			rects[i].y = rect.y;
			rects[i].w = width + (i == N - 1 ? rest : 0);
			rects[i].h = rect.h;
		}

		return rects;
	}




	// -- R E C T  T Y P E S --------------------------------------------------

	/* float rect */
	using rect_float = rect<float>;

	/* double rect */
	using rect_double = rect<double>;

	/* int rect */
	using rect_int = rect<int>;

	/* unsigned rect */
	using rect_uint = rect<unsigned>;


}

#endif

