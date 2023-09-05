#include "escape.hpp"


/* move home */
const xns::escape::view& xns::escape::move_home(void) {
	// return escape sequence
	return _escapes[esctype::MOVE_HOME];
}



/* erase screen */
const xns::escape::view& xns::escape::erase_screen(void) {
	// return escape sequence
	return _escapes[esctype::ERASE_SCREEN];
}

/* erase line */
const xns::escape::view& xns::escape::erase_line(void) {
	// return escape sequence
	return _escapes[esctype::ERASE_LINE];
}

/* erase to end of line */
const xns::escape::view& xns::escape::erase_to_end(void) {
	// return escape sequence
	return _escapes[esctype::ERASE_TO_END];
}

/* erase from start of line */
const xns::escape::view& xns::escape::erase_from_start(void) {
	// return escape sequence
	return _escapes[esctype::ERASE_FROM_START];
}


/* enter screen */
const xns::escape::view& xns::escape::enter_screen(void) {
	// return escape sequence
	return _escapes[esctype::ENTER_SCREEN];
}

/* exit screen */
const xns::escape::view& xns::escape::exit_screen(void) {
	// return escape sequence
	return _escapes[esctype::EXIT_SCREEN];
}

/* save screen */
const xns::escape::view& xns::escape::save_screen(void) {
	// return escape sequence
	return _escapes[esctype::SAVE_SCREEN];
}

/* restore screen */
const xns::escape::view& xns::escape::restore_screen(void) {
	// return escape sequence
	return _escapes[esctype::RESTORE_SCREEN];
}


/* reset style */
const xns::escape::view& xns::escape::reset_style(void) {
	// return escape sequence
	return _escapes[esctype::RESET_STYLE];
}


/* show cursor */
const xns::escape::view& xns::escape::show_cursor(void) {
	// return escape sequence
	return _escapes[esctype::SHOW_CURSOR];
}

/* hide cursor */
const xns::escape::view& xns::escape::hide_cursor(void) {
	// return escape sequence
	return _escapes[esctype::HIDE_CURSOR];
}

/* request position */
const xns::escape::view& xns::escape::request_position(void) {
	// return escape sequence
	return _escapes[esctype::REQUEST_POSITION];
}


/* cursor beam */
const xns::escape::view& xns::escape::cursor_beam(void) {
	// return escape sequence
	return _escapes[esctype::CURSOR_BEAM];
}

/* cursor underline */
const xns::escape::view& xns::escape::cursor_underline(void) {
	// return escape sequence
	return _escapes[esctype::CURSOR_UNDERLINE];
}

/* cursor block */
const xns::escape::view& xns::escape::cursor_block(void) {
	// return escape sequence
	return _escapes[esctype::CURSOR_BLOCK];
}



/* move left */
xns::escape::string xns::escape::move_left(const size_type cells) {
	// return escape sequence
	return _move_direction(cells, 'D');
}

/* move right */
xns::escape::string xns::escape::move_right(const size_type cells) {
	// return escape sequence
	return _move_direction(cells, 'C');
}

/* move up */
xns::escape::string xns::escape::move_up(const size_type cells) {
	// return escape sequence
	return _move_direction(cells, 'A');
}

/* move down */
xns::escape::string xns::escape::move_down(const size_type cells) {
	// return escape sequence
	return _move_direction(cells, 'B');
}




#define BUFFER_SIZE_POS			32
#define ZERO_ASCII				48
#define BASE					10
#define ESCAPE_BUFFER_SIZE		64
#define FOREGROUND				true
#define BACKGROUND				false









static bool bracket(const char c) {
	return false;
}


using proto = bool(*)(const char);

static constexpr proto _table[1] {
	&bracket
};



bool xns::escape::request_position(size_type& x, size_type& y) {

	size_type* num     = &y;
	bool       bracket = false;
	xns::ubyte     c       = 0;

	constexpr xns::ubyte base = 10;
	constexpr xns::ubyte zero = 48;

	const view& esc = _escapes[esctype::REQUEST_POSITION];

	::write(STDOUT_FILENO, esc.data(), esc.size());
	x = y = 0;
	// iterate while input available
	while (0 < read(STDIN_FILENO, &c, 1) && c != 'R') {
		// check bracket sequence
		if (bracket) {
			// convert character to integer
			if ((c ^ 48) < base) {

				term_size digit = c - zero;

				// check overflow
				term_size tmp = (xns::limits::max<term_size>() - digit) / base;

				if (*num > tmp) return false;

				*num = (*num * base) + digit;

			}
			// check separator character
			else if (c == ';') num = &x;
		} // check control character
		else if (c == '[') bracket = true;
	}
	--x; --y;
	// final check sequence
	return (bracket && c == 'R');
}







// -- M O V E -----------------------------------------------------------------


/* get move position */
xns::escape::string xns::escape::move_position(size_type x, size_type y) {
	// ESC[{line};{column}H

	char_t  escape[ESCAPE_BUFFER_SIZE];
	xns::size_t ite;

	constexpr const xns::size_t max = xns::limits::max<size_type>();

	x += (x != max);
	y += (y != max);

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
	return xns::string(&escape[ite], ESCAPE_BUFFER_SIZE - ite);
}



/* move direction */
xns::escape::string xns::escape::_move_direction(size_type cells, const char_t dir) {
	// static returned string
	//static Xf::CString escape;
	// compile time buffer size
	constexpr const xns::size_t size = 3 + xns::limits::digits<xns::term_size>();

	// buffer
	char_t buffer[size];

	// init iterator to last index
	xns::size_t i = size - 1;

	// direction character
	buffer[i] = dir;

	// integer to ascii X pos
	while (cells) {
		buffer[--i] = ((cells % BASE) ^ ZERO_ASCII);
		cells /= BASE;
	}

	// ctrl character
	buffer[--i] = '[';
	// escape character
	buffer[--i] = '\x1b';

	// append escape sequence to buffer
	return xns::string(&buffer[i], size - i);
}




/* move x position */
const xns::escape::string& xns::escape::move_x(size_type x) {

	// static returned string
	static string escape;

	// compile time buffer size
	constexpr const xns::size_t size = sizeof("\x1b[G")
								+ xns::limits::digits<xns::term_size>();
	// buffer
	char_t buffer[size];

	// init iterator
	xns::size_t i = size - 1;

	// increment x if not max
	x += (x != xns::limits::max<xns::term_size>());

	// last character
	buffer[i] = 'G';

	// integer to ascii X pos
	while (x) {
		buffer[--i] = ((x % BASE) ^ ZERO_ASCII);
		x /= BASE;
	}

	// ctrl character
	buffer[--i] = '[';

	// escape character
	buffer[--i] = '\x1b';

	// assign escape sequence to string
	escape.assign(&buffer[i], size - i);

	// return escape
	return escape;
}



// -- C O L O R ---------------------------------------------------------------


/* hex color */
xns::escape::string xns::escape::hex_color(const xns::hexcolor color, const bool fore) {

	// declare bytes color
	xns::ubyte r, g, b;
	// get color layer
	r = (color >> 16) & 0xFF;
	g = (color >> 8)  & 0xFF;
	b = (color)       & 0xFF;

	return rgb_color(r, g, b, fore);
}

/* color rgb */
xns::escape::string xns::escape::rgb_color(xns::u8 r, xns::u8 g, xns::u8 b, const bool fore) {
	// static 24bit color escape sequence
	static xns::ubyte escape[] = {	'\x1b', '[',
									' ', '8', ';', '2', ';',
									'0', '0', '0', ';',
									'0', '0', '0', ';',
									'0', '0', '0', 'm', '\0'
	};
	constexpr xns::size_t r_off = 0x6;
	constexpr xns::size_t g_off = 0xA;
	constexpr xns::size_t b_off = 0xE;

	// foreground / background char
	escape[2] =  fore == true ? '3' : '4';
	// integer to ascii
	for (xns::size_t x = 3; x; --x) {
		// red integer to ascii
		escape[x + r_off] = ((r % BASE) ^ ZERO_ASCII);
		// green integer to ascii
		escape[x + g_off] = ((g % BASE) ^ ZERO_ASCII);
		// blue integer to ascii
		escape[x + b_off] = ((b % BASE) ^ ZERO_ASCII);
		// remove last digit
		r /= BASE; g /= BASE; b /= BASE;
	} // append escape sequence to buffer
	return xns::string((char*)escape, 19);
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






// ESC[#E	moves cursor to beginning of next line, # lines down
// ESC[#F	moves cursor to beginning of previous line, # lines up

// ESC M	moves cursor one line up, scrolling if needed



////////////////////////// ERASE FUNCTIONS
// Erasing the line won't move the cursor,
// meaning that the cursor will stay at the last position
// it was at before the line was erased.
// You can use \r after erasing the line,
// to return the cursor to the start of the current line.
/////////////////////////////////////////////////////////

// erase from cursor until end of screen
//#define AAA									ESC"[0J"
// erase from cursor to beginning of screen
//#define BBB									ESC"[1J"
// erase saved lines
//#define CCC									ESC"[3J"


/////////////////////// COMMON PRIVATE MODES
// These are some examples of private modes,
// which are not defined by the specification,
// but are implemented in most terminals.
// Refer to the XTerm Control Sequences
// for a more in-depth list of private modes defined by XTerm.
// While these modes may be supported by the most terminals,
// some may not work in multiplexers like tmux.
///////////////////////////////////////////////


//ESC[0m		reset all modes (styles and colors)
//ESC[1m	ESC[22m	set bold mode.
//ESC[2m	ESC[22m	set dim/faint mode.
//ESC[3m	ESC[23m	set italic mode.
//ESC[4m	ESC[24m	set underline mode.
//ESC[5m	ESC[25m	set blinking mode
//ESC[7m	ESC[27m	set inverse/reverse mode
//ESC[8m	ESC[28m	set hidden/invisible mode
//ESC[9m	ESC[29m	set strikethrough mode.
