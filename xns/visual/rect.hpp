#ifndef RECT_HEADER
#define RECT_HEADER

#include <iostream>

#include "types.hpp"
#include "is_arithmetic.hpp"
#include "move.hpp"


#define PRECT(rect) std::cout << "Rect(" << rect.x << ", " << rect.y << ", " << rect.w << ", " << rect.h << ")" << std::endl;


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E C T  S T R U C T ------------------------------------------------

	template <class T>
	struct rect final {


		// -- assertions ------------------------------------------------------

		/* check T is an arithmetic type */
		static_assert(xns::is_arithmetic<T>, "): T MUST BE AN ARITHMETIC TYPE :(");


		// -- types -----------------------------------------------------------

		/* self type */
		using self = rect<T>;

		/* size type */
		using size_type = T;


		// -- members ---------------------------------------------------------

		size_type x, y, w, h;


		// -- constructors ----------------------------------------------------

		/* default constructor */
		rect(void) noexcept
		: x{0}, y{0}, w{0}, h{0} {}

		/* size and position constructor */
		rect(   const size_type x,
				const size_type y,
				const size_type w,
				const size_type h) noexcept
		: x{x}, y{y}, w{w}, h{h} {}

		/* copy constructor */
		rect(const self& other) noexcept
		: x{other.x}, y{other.y}, w{other.w}, h{other.h} {}

		/* move constructor */
		rect(self&& other) noexcept
		: rect{other} {}

		/* destructor */
		~rect(void) noexcept = default;


		// -- assignment operators --------------------------------------------

		/* copy assignment operator */
		self& operator=(const self& other) noexcept {
			// check for self assignment
			if (this != &other) {
				// copy dimension
				w = other.w; h = other.h;
				// copy position
				x = other.x; y = other.y;
			} // return self reference
			return *this;
		}

		/* move assignment operator */
		self& operator=(self&& other) noexcept {
			// call copy assignment
			return operator=(other);
		}


		// -- boolean operators -----------------------------------------------

		/* bool operator */
		explicit operator bool(void) const noexcept {
			// check if empty
			return !empty();
		}

		/* bool not operator */
		bool operator!(void) const noexcept {
			// check if empty
			return empty();
		}


		// -- comparison operators --------------------------------------------

		/* equality operator */
		bool operator==(const self& other) const noexcept {
			// return equality
			return x == other.x && y == other.y && w == other.w && h == other.h;
		}


		// -- accessors -------------------------------------------------------

		/* empty */
		bool empty(void) const noexcept {
			// check if empty
			return w == 0 || h == 0;
		}


	};


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

