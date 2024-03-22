#ifndef XNS_RECT_HEADER
#define XNS_RECT_HEADER

#include <iostream>

#include "type_traits/types.hpp"
#include "containers/array.hpp"
#include "type_traits/type_categories/is_arithmetic.hpp"


#define PRECT(rect) std::cout << "Rect(" << rect.x() << ", " << rect.y() << ", " << rect.w() << ", " << rect.h() << ")" << std::endl;


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E C T -------------------------------------------------------------

	template <typename P, typename D = P>
	class rect final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::rect<P, D>;

			/* position type */
			using pos_type = P;

			/* dimension type */
			using dim_type = D;


		private:

			// -- private members ---------------------------------------------

			/* position */
			pos_type _x, _y;

			/* dimension */
			dim_type _w, _h;


		public:


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline constexpr rect(void) noexcept
			: _x{0}, _y{0}, _w{0}, _h{0} {}

			/* size and position constructor */
			inline constexpr rect(const pos_type x,
								  const pos_type y,
								  const dim_type w,
								  const dim_type h) noexcept
			: _x{x}, _y{y}, _w{w}, _h{h} {}

			/* copy constructor */
			constexpr rect(const self&) noexcept = default;

			/* move constructor */
			constexpr rect(self&&) noexcept = default;

			/* destructor */
			~rect(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&) noexcept -> self& = default;


			// -- public accessors --------------------------------------------

			/* empty */
			inline constexpr auto empty(void) const noexcept -> bool {
				return _w == 0 || _h == 0;
			}

			/* x */
			inline constexpr auto x(void) noexcept -> pos_type& {
				return _x;
			}

			/* const x */
			inline constexpr auto x(void) const noexcept -> const pos_type& {
				return _x;
			}

			/* y */
			inline constexpr auto y(void) noexcept -> pos_type& {
				return _y;
			}

			/* const y */
			inline constexpr auto y(void) const noexcept -> const pos_type& {
				return _y;
			}

			/* w */
			inline constexpr auto w(void) noexcept -> dim_type& {
				return _w;
			}

			/* const w */
			inline constexpr auto w(void) const noexcept -> const dim_type& {
				return _w;
			}

			/* h */
			inline constexpr auto h(void) noexcept -> dim_type& {
				return _h;
			}

			/* const h */
			inline constexpr auto h(void) const noexcept -> const dim_type& {
				return _h;
			}


			// -- public modifiers --------------------------------------------

			/* x */
			inline constexpr auto x(const pos_type& x) noexcept -> void {
				_x = x;
			}

			/* y */
			inline constexpr auto y(const pos_type& y) noexcept -> void {
				_y = y;
			}

			/* w */
			inline constexpr auto w(const dim_type& w) noexcept -> void {
				_w = w;
			}

			/* h */
			inline constexpr auto h(const dim_type& h) noexcept -> void {
				_h = h;
			}


			// -- public conversion operators ---------------------------------

			/* bool conversion operator */
			inline constexpr explicit operator bool(void) const noexcept {
				return not empty();
			}


			// -- public boolean operators ------------------------------------

			/* not operator */
			inline constexpr auto operator!(void) const noexcept -> bool {
				return empty();
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			inline constexpr auto operator==(const self& other) const noexcept -> bool {
				return _w == other._w && _h == other._h;
			}

			/* inequality operator */
			inline constexpr auto operator!=(const self& other) const noexcept -> bool {
				return !operator==(other);
			}

			/* less than operator */
			inline constexpr auto operator<(const self& other) const noexcept -> bool {
				return (_w * _h) < (other._w * other._h);
			}

			/* less than or equal operator */
			inline constexpr auto operator<=(const self& other) const noexcept -> bool {
				return *this < other || *this == other;
			}

			/* greater than operator */
			inline constexpr auto operator>(const self& other) const noexcept -> bool {
				return !operator<=(other);
			}

			/* greater than or equal operator */
			inline constexpr auto operator>=(const self& other) const noexcept -> bool {
				return !operator<(other);
			}


	}; // class rect


	// -- R E C T  F U N C T I O N S ------------------------------------------

	template <decltype(sizeof(0)) N, typename P, typename D>
	constexpr auto horizontal_split(const xns::rect<P, D>& rect) noexcept -> xns::array<xns::rect<P, D>, N> {
		//
		//// check N is not zero
		//static_assert(N > 0, "horizontal_split: cannot divide by zero");
		//
		//// check N
		//
		//D width = rect.w / N;
		//D rest = rect.w % N;
		//
		//
		//xns::array<xns::rect<P, D>, N> rects;
		//
		//for (decltype(N) i = 0; i < N; ++i) {
		//	rects[i].x = rect.x + (i * width);
		//	rects[i].y = rect.y;
		//	rects[i].w = width + (i == N - 1 ? rest : 0);
		//	rects[i].h = rect.h;
		//}
		//
		return {};
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

