#ifndef ESCAPE_HEADER
#define ESCAPE_HEADER

#include <unistd.h>
#include <iostream>


#include "Types.hpp"
#include "Color.hpp"
#include "Buffer.hpp"
#include "Macro.hpp"

#define ESC						"\x1b"

// ESC[#A	moves cursor up # lines
// ESC[#B	moves cursor down # lines
// ESC[#C	moves cursor right # columns
// ESC[#D	moves cursor left # columns
// ESC[#E	moves cursor to beginning of next line, # lines down
// ESC[#F	moves cursor to beginning of previous line, # lines up
// ESC[#G	moves cursor to column #
// ESC M	moves cursor one line up, scrolling if needed

#define MOVE_HOME				ESC"[H"

#define MOVE_LEFT				ESC"[1D"
#define MOVE_RIGHT				ESC"[1C"


////////////////////////// ERASE FUNCTIONS
// Erasing the line won't move the cursor,
// meaning that the cursor will stay at the last position
// it was at before the line was erased.
// You can use \r after erasing the line,
// to return the cursor to the start of the current line.
/////////////////////////////////////////////////////////

// erase from cursor until end of screen
#define AAA									ESC"[0J"
// erase from cursor to beginning of screen
#define BBB									ESC"[1J"
// erase saved lines
#define CCC									ESC"[3J"


// erase from cursor to end of line
#define ERASE_FROM_CURSOR_TO_EOL			ESC"[0K"
// erase start of line to the cursor
#define ERASE_START_OF_LINE_TO_CURSOR		ESC"[1K"
// erase the entire line
#define ERASE_LINE							ESC"[2K"
// erase entire screen
#define ERASE_SCREEN						ESC"[2J"



// request cursor position (format ESC[#;#R)
#define REQUEST_CURSOR_POSITION				ESC"[6n"

#define CURSOR_BEAM							ESC"[5 q"

#define CURSOR_UNDERLINE					ESC"[3 q"

#define CURSOR_BLOCK						ESC"[1 q"


// make cursor visible
#define SHOW_CURSOR							ESC"[?25h"
// make cursor invisible
#define NO_CURSOR							ESC"[?25l"


/////////////////////// COMMON PRIVATE MODES
// These are some examples of private modes,
// which are not defined by the specification,
// but are implemented in most terminals.
// Refer to the XTerm Control Sequences
// for a more in-depth list of private modes defined by XTerm.
// While these modes may be supported by the most terminals,
// some may not work in multiplexers like tmux.
///////////////////////////////////////////////

// enables the alternative buffer
#define ENTER_SCREEN						ESC"[?1049h"
// disables the alternative buffer
#define EXIT_SCREEN							ESC"[?1049l"
// restore screen
#define RESTORE_SCREEN						ESC"[?47l"
// save screen
#define SAVE_SCREEN							ESC"[?47h"


#define RESET_STYLE							ESC"[0m"

//ESC[0m		reset all modes (styles and colors)
//ESC[1m	ESC[22m	set bold mode.
//ESC[2m	ESC[22m	set dim/faint mode.
//ESC[3m	ESC[23m	set italic mode.
//ESC[4m	ESC[24m	set underline mode.
//ESC[5m	ESC[25m	set blinking mode
//ESC[7m	ESC[27m	set inverse/reverse mode
//ESC[8m	ESC[28m	set hidden/invisible mode
//ESC[9m	ESC[29m	set strikethrough mode.



#define BUFFER_SIZE_POS			32
#define ZERO_ASCII				48
#define BASE					10
#define ESCAPE_BUFFER_SIZE		64
#define FOREGROUND				true
#define BACKGROUND				false




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
