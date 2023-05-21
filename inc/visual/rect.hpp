#ifndef RECT_HEADER
#define RECT_HEADER

#include <iostream>
#include "types.hpp"

#define PRECT(rect) std::cout << "Rect(" << rect.x << ", " << rect.y << ", " << rect.w << ", " << rect.h << ")" << std::endl;


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- R E C T  S T R U C T ------------------------------------------------

	struct rect final {


		// -- A L I A S E S ---------------------------------------------------

		/* size type */
		using size_type = xns::size_t;


		// -- M E M B E R S ---------------------------------------------------

		size_type x, y, w, h;


		// -- C O N S T R U C T O R S -----------------------------------------

		/* default constructor */
		rect(void) noexcept;

		/* size and position constructor */
		rect(   const size_type x,
				const size_type y,
				const size_type w,
				const size_type h) noexcept;

		/* copy constructor */
		rect(const rect& other) noexcept;

		/* move constructor */
		rect(rect&& other) noexcept;

		/* destructor */
		~rect(void) noexcept;


		// -- O P E R A T O R S -----------------------------------------------

		/* copy assignment operator */
		rect& operator=(const rect& other) noexcept;

		/* move assignment operator */
		rect& operator=(rect&& other) noexcept;

		/* bool operator */
		explicit operator bool(void) const noexcept;

		/* bool not operator */
		bool operator!(void) const noexcept;

		/* equality operator */
		bool operator==(const rect& other) const noexcept;

		// -- M E T H O D S ---------------------------------------------------

		/* empty */
		bool empty(void) const noexcept;


	};


}

#endif

