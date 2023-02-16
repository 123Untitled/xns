#ifndef RECT_HEADER
#define RECT_HEADER

#include "types.hpp"

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- R E C T  S T R U C T ------------------------------------------------

	struct Rect final {

		// -- A L I A S E S ---------------------------------------------------

		/* size type */
		using Size = UInt64;


		// -- M E M B E R S ---------------------------------------------------

		Size x, y, w, h;


		// -- C O N S T R U C T O R S -----------------------------------------

		/* default constructor */
		Rect(void) noexcept;

		/* size and position constructor */
		Rect(   const Size x,
				const Size y,
				const Size w,
				const Size h) noexcept;

		/* copy constructor */
		Rect(const Rect& other) noexcept;

		/* move constructor */
		Rect(Rect&& other) noexcept;

		/* destructor */
		~Rect(void) noexcept;


		// -- O P E R A T O R S -----------------------------------------------

		/* copy assignment operator */
		Rect& operator=(const Rect& other) noexcept;

		/* move assignment operator */
		Rect& operator=(Rect&& other) noexcept;


	};

};

#endif

