#ifndef ESCAPE_HEADER
#define ESCAPE_HEADER

#include <unistd.h>
#include <iostream>


#include "types.hpp"
#include "Color.hpp"
#include "Buffer.hpp"
#include "Macro.hpp"
#include "array.hpp"


// -- E S C A P E  N A M E S P A C E ------------------------------------------

namespace Escape {

	// -- F U N C T I O N S ---------------------------------------------------

	bool requestCursorPosition(UInt32& x, UInt32& y);



	// -- M O V E -------------------------------------------------------------

	/* move position */
	void move_position(UInt32 x, UInt32 y);

	/* move left */
	void move_left(void);

	/* move right */
	void move_right(void);

	/* move home */
	void move_home(void);


	// -- E R A S E -----------------------------------------------------------

	void eraseFromCursorToEOL(void);

	/* erase line */
	void erase_line(void);


	// -- S C R E E N ---------------------------------------------------------

	/* enter screen */
	void enter_screen(void);

	/* exit screen */
	void exit_screen(void);

	/* clear screen */
	void clear_screen(void);


	// -- C O L O R -----------------------------------------------------------

	/* color rgb */
	void color_rgb(const UInt32 color, const bool fore = true);

	/* reset style */
	void reset_style(void);


	// -- C U R S O R ---------------------------------------------------------

	/* show cursor */
	void show_cursor(void);

	/* hide cursor */
	void hide_cursor(void);


	// -- C U R S O R  S T Y L E ----------------------------------------------

	/* cursor beam */
	void cursor_beam(void);

	/* cursor underline */
	void cursor_underline(void);

	/* cursor block */
	void cursor_block(void);

};

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- E S C A P E  C L A S S ----------------------------------------------

	class Escape final {




		public:

			// -- A L I A S E S -----------------------------------------------

			/* character type */
			using Char = char;

			// -- C O N S T R U C T O R S -------------------------------------

			/* non-instantiable class */
			NON_INSTANCIABLE(Escape);

		private:


			// -- M E M B E R S -----------------------------------------------

			/* move home \e[H */
			constexpr static const Xf::Array move_home{"\x1b[H"};

			/* move left \e[D */
			constexpr static const Xf::Array move_left{"\x1b[D"};

			/* move right \e[C */
			constexpr static const Xf::Array move_right = { '\x1b', '[', 'C' };

			/* move up \e[A */
			constexpr static const Xf::Array move_up = { '\x1b', '[', 'A' };

			/* move down \e[B */
			constexpr static const Xf::Array move_down = { '\x1b', '[', 'B' };



	};

};



#endif
