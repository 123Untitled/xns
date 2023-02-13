#include "escape.hpp"

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


bool Escape::requestCursorPosition(UInt32& x, UInt32& y) {

	UInt32*	num		= &y;
	bool	bracket	= false;
	char	c		= 0;

	write(STDOUT_FILENO, REQUEST_CURSOR_POSITION,
		sizeof(REQUEST_CURSOR_POSITION));
	x = y = 0;
	// iterate while input available
	while (0 < read(STDIN_FILENO, &c, 1) && c != 'R') {
		write(1, &c, 1);
		if (bracket) {
			// convert character to integer
			if ((c ^ 48) < 10)
				*num = (*num * 10) + (c - 48);
			// check separator character
			else if (c == ';') num = &x;
		} // check control character
		else if (c == '[') bracket = true;
	} // final check sequence
	return (bracket && x && y && c == 'R');
}







// -- M O V E -----------------------------------------------------------------

/* move position */
void Escape::move_position(UInt32 x, UInt32 y) {
	UInt8		escape[ESCAPE_BUFFER_SIZE];
	UInt32		ite;
	// init iterator
	ite = ESCAPE_BUFFER_SIZE - 1;
	// last char
	escape[ite] = 'H';
	// integer to ascii X pos
	while (x) {
		escape[--ite] = ((x % BASE) ^ ZERO_ASCII);
		x /= BASE;
	} // separator char
	escape[--ite] = ';';
	// integer to ascii Y pos
	while (y) {
		escape[--ite] = ((y % BASE) ^ ZERO_ASCII);
		y /= BASE;
	} // ctrl char
	escape[--ite] = '[';
	// escape char
	escape[--ite] = '\x1b';

	// append escape sequence to buffer
	Buffer::draw((char*)&escape[ite], ESCAPE_BUFFER_SIZE - ite);
}

/* move left */
void Escape::move_left(void) {
	// append escape sequence to buffer
	Buffer::draw(MOVE_LEFT, sizeof(MOVE_LEFT));
}

/* move right */
void Escape::move_right(void) {
	// append escape sequence to buffer
	Buffer::draw(MOVE_RIGHT, sizeof(MOVE_RIGHT));
}

/* move home */
void Escape::move_home(void) {
	// append escape sequence to buffer
	Buffer::draw(MOVE_HOME, sizeof(MOVE_HOME));
}


// -- E R A S E ---------------------------------------------------------------

//SInt32 Escape::eraseFromCursorToEOL(void) {
void Escape::eraseFromCursorToEOL(void) {
	Buffer::draw(ERASE_FROM_CURSOR_TO_EOL, sizeof(ERASE_FROM_CURSOR_TO_EOL));
	//return (write(STDOUT_FILENO, ERASE_FROM_CURSOR_TO_EOL, sizeof(ERASE_FROM_CURSOR_TO_EOL)));
}

/* erase line */
void Escape::erase_line(void) {
	// append escape sequence to buffer
	Buffer::draw(ERASE_LINE, sizeof(ERASE_LINE));
}


// -- S C R E E N -------------------------------------------------------------

/* enter screen */
void Escape::enter_screen(void) {
	// append escape sequence to buffer
	Buffer::draw(ENTER_SCREEN, sizeof(ENTER_SCREEN));
}

/* exit screen */
void Escape::exit_screen(void) {
	// append escape sequence to buffer
	Buffer::draw(EXIT_SCREEN, sizeof(EXIT_SCREEN));
}

/* clear screen */
void Escape::clear_screen(void) {
	// append escape sequence to buffer
	Buffer::draw(ERASE_SCREEN, sizeof(ERASE_SCREEN));
}


// -- C O L O R ---------------------------------------------------------------

/* color rgb */
void Escape::color_rgb(const UInt32 color, const bool fore) {
	// static 24bit color escape sequence
	static UInt8	escape[] = {	'\x1b', '[',
									' ', '8', ';', '2', ';',
									'0', '0', '0', ';',
									'0', '0', '0', ';',
									'0', '0', '0', 'm', '\0'
	};
	#define RED_OFFSET		0x6
	#define GREEN_OFFSET	0xA
	#define BLUE_OFFSET		0xE
	// declare bytes color
	UInt8 r, g, b;
	// get color layer
	r = color >> 16    & 0xFF;
	g = color >> 8	  & 0xFF;
	b = color		 & 0xFF;
	// foreground / background char
	escape[2] =  fore == true ? '3' : '4';
	// integer to ascii
	for (UInt32 x = 3; x; --x) {
		// red integer to ascii
		escape[x + RED_OFFSET]		= ((r % BASE) ^ ZERO_ASCII);
		// green integer to ascii
		escape[x + GREEN_OFFSET]	= ((g % BASE) ^ ZERO_ASCII);
		// blue integer to ascii
		escape[x + BLUE_OFFSET]		= ((b % BASE) ^ ZERO_ASCII);
		// remove last digit
		r /= BASE; g /= BASE; b /= BASE;
	} // append escape sequence to buffer
	Buffer::draw(escape, 19);
}

/* reset style */
void Escape::reset_style(void) {
	// append escape sequence to buffer
	Buffer::draw(RESET_STYLE, sizeof(RESET_STYLE));
}


// -- C U R S O R -------------------------------------------------------------

/* show cursor */
void Escape::show_cursor(void) {
	// append escape sequence to buffer
	Buffer::draw(SHOW_CURSOR, sizeof(SHOW_CURSOR));
}

/* hide cursor */
void Escape::hide_cursor(void) {
	// append escape sequence to buffer
	Buffer::draw(NO_CURSOR, sizeof(NO_CURSOR));
}


// -- C U R S O R  S T Y L E --------------------------------------------------

/* cursor beam */
void Escape::cursor_beam(void) {
	// append escape sequence to buffer
	Buffer::draw(CURSOR_BEAM, sizeof(CURSOR_BEAM));
}

/* cursor underline */
void Escape::cursor_underline(void) {
	// append escape sequence to buffer
	Buffer::draw(CURSOR_UNDERLINE, sizeof(CURSOR_UNDERLINE));
}

/* cursor block */
void Escape::cursor_block(void) {
	// append escape sequence to buffer
	Buffer::draw(CURSOR_BLOCK, sizeof(CURSOR_BLOCK));
}












//bool checkEscape(const char c) {
//	return (c == 27); }
//
//bool checkBracket(const char c) {
//	return (c == '['); }
//
//bool checkSemicolon(const char c) {
//	return (c == ';'); }
//
//bool checkEnd(const char c) {
//	return (c == 'R'); }
//
//bool checkNumber(const char c) {
//	return ((c ^ 48) < 10); }
//
//
//bool Escape::requestCursorPosition(UInt& x, UInt& y) {
//
//	using Func = decltype(&checkEnd);
//
//	static Func funcs[4] = {
//		checkEscape,
//		checkBracket,
//		checkSemicolon,
//		checkEnd
//	};
//	std::string buff;
//
//	UInt*	num		= &y;
//	char	c		= 0;
//	UInt	i		= 0;
//
//	write(STDOUT_FILENO, REQUEST_CURSOR_POSITION "z",
//		sizeof(REQUEST_CURSOR_POSITION)+1);
//	x = y = 0;
//	// iterate while input available
//	/*while (read(STDIN_FILENO, &c, 1) > 0 && c != 'R') {
//		buff.push_back(c);
//		if (c == 27) c = 'E';
//		std::cout << "readed: " <<  c << std::endl;
//	}*/
//	char bb[128 + 1];
//	int readed = read(0, bb, 128);
//	std::cout << "readed char: " << readed << std::endl;
//
//	bb[readed] = '\0';
//
//	buff.assign(bb);
//
//	for (size_t i = 0; i < buff.size(); ++i) {
//
//		char ch = buff[i];
//
//		if (ch == 27)
//			write(1, "esc", 3);
//		else {
//			write(1, &ch, 1);
//		}
//	}
//
//	std::cout << "\n" << std::endl;
//
//		//if (funcs[i](c))
//		//	i++;
//
//
//
//	return (true);
//
//
//
//
//
//
//
//		/*
//
//		if (escape) {
//
//			if (bracket) {
//
//				// convert character to integer
//				if ((c ^ 48) < 10)	{ *num = (*num * 10) + (c - 48); }
//
//				// check separator character
//				else if (c == ';')	{ num = &x; }
//
//				else if (c == 'R')	{ break; }
//
//				else				{ return (false); }
//			}
//
//			// check control character
//			else if (c == '[')	{ bracket = true; }
//			else				{ return (false); }
//		}
//
//		else if (c == 27)	{ escape = true;	}
//		else				{ return (false);	}
//		*/
//
//	//} // final check sequence
//	//return (true);
//}
