#ifndef ESCAPE_HEADER
#define ESCAPE_HEADER

#include <unistd.h>
#include <iostream>


#include "Types.hpp"
#include "Color.hpp"
#include "Buffer.hpp"
#include "Macro.hpp"


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

#endif
