#ifndef ESCAPE_HEADER
#define ESCAPE_HEADER

#include <unistd.h>
#include <string>
typedef std::string String;

#include "Types.hpp"
#include "Color.hpp"

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

//ESC[0m		reset all modes (styles and colors)
//ESC[1m	ESC[22m	set bold mode.
//ESC[2m	ESC[22m	set dim/faint mode.
//ESC[3m	ESC[23m	set italic mode.
//ESC[4m	ESC[24m	set underline mode.
//ESC[5m	ESC[25m	set blinking mode
//ESC[7m	ESC[27m	set inverse/reverse mode
//ESC[8m	ESC[28m	set hidden/invisible mode
//ESC[9m	ESC[29m	set strikethrough mode.
/*enum {

};*/



#define BUFFER_SIZE_POS			32
#define ZERO_ASCII				48
#define BASE					10
#define ESCAPE_BUFFER_SIZE		64
#define FOREGROUND				true
#define BACKGROUND				false


class Esc {
	private:
	const UInt8*	_ptr;
	UInt64			_size;
	public:
	Esc(void);
	Esc(const Esc& copy);
	Esc(const UInt8* ptr, const UInt64 size);
	~Esc(void);
	Esc& operator=(const Esc&);
	const UInt8* ptr(void) const;
	UInt64		size(void) const;
};



class Escape {

private:

	static const char*		_escapes[];


	public:

	static Esc			getEscapeSequence(void);

	static bool			requestCursorPosition(UInt32& x, UInt32& y);

	/////////////////////////////////////////////
	static SInt32		movePos(UInt32 x, UInt32 y);
	static Esc			movePosEsc(UInt32 x, UInt32 y);

	static SInt32		moveLeft(void);
	static SInt32		moveRight(void);
	static SInt32		moveHome(void);
	static SInt32		eraseFromCursorToEOL(void);
	// DRAW /////////////////////////
	// SCREEN ////////////////////
	static SInt32		enterScreen();
	static SInt32		exitScreen();
	static SInt32		clearScreen();
	// COLOR /////////////////////
	static Esc			set24bitColor(const UInt32 color, const bool fore);
	//static SInt32		set24bitColor(const UInt32 color, const bool fore);
	static SInt32		resetColor(void);
	/////////////////////////////////
	// CURSOR ///////////////
	static SInt32		showCursor();
	static SInt32		noCursor();
	static SInt32		cursorBeam();
	static SInt32		cursorUnderline();
	static SInt32		cursorBlock();

};

#endif
