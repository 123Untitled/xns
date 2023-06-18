#ifndef DRAW_HEADER
#define DRAW_HEADER

#include <unistd.h>

// libxfunc
#include "escape.hpp"
#include "types.hpp"
#include "ascii.hpp"
#include "macro.hpp"
#include "output.hpp"

/* standard includes */
#include <string>

#define PDELAY		40000


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- D R A W  C L A S S --------------------------------------------------

	class draw final {

		public:

			// -- C O N S T R U C T O R S -----------------------------------------

			/* non-instanciable class */
			NON_INSTANCIABLE(draw);


			/* draw line */
			static void draw_line(const xns::u32, const xns::u32, const void*, const xns::u32);

			/* draw string */
			static void draw_string(const xns::u32, const xns::u32, const xns::string&);

			/* vertical draw */
			static void vertival_draw(const xns::u32 x, xns::u32 y, const void *ptr, const xns::u32 size, xns::u32 line);

			/* clear line */
			static void clear_line(const xns::u32, const xns::u32, const xns::u32);

			/* draw integer */
			static void draw_integer(const xns::u32);

			static int drawStringNl(const xns::string& string);

			static void animateDraw(const xns::string& string);
			static void animateDrawNl(const xns::string& string);
			static void animateDraw(const xns::string& string, const xns::u32 colorIn, const xns::u32 colorOut);

	};


}

#endif
