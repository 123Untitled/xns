#include "escape.hpp"

#define ESC "\x1b"

const Xf::Escape::Array Xf::Escape::_escapes = {
	/* move home */
	ESC"[H",
	/* move left */
	ESC"[1D",
	/* move right */
	ESC"[1C",

	/* erase screen */
	ESC"[2J",
	/* erase line */
	ESC"[2K",
	/* erase to end of line */
	ESC"[0K",
	/* erase from start of line */
	ESC"[1K",

	/* enter screen */
	ESC"[?1049h",
	/* exit screen */
	ESC"[?1049l",
	/* save screen */
	ESC"[?47h",
	/* restore screen */
	ESC"[?47l",

	/* reset style */
	ESC"[0m",

	/* show cursor */
	ESC"[?25h",
	/* hide cursor */
	ESC"[?25l",
	/* request position */
	ESC"[6n",

	/* cursor beam */
	ESC"[5 q",
	/* cursor underline */
	ESC"[3 q",
	/* cursor block */
	ESC"[1 q"
};

#undef ESC


/* get escape sequence */
const Xf::CString& Xf::Escape::get(const Esctype type) {
	return _escapes[IDX(type) % IDX(Esctype::ESCTYPE_MAX)];
}


/* move home */
void Xf::Escape::move_home(void) {
	Xf::Output::write(_escapes[IDX(Esctype::MOVE_HOME)]);
}

/* move left */
void Xf::Escape::move_left(void) {
	Xf::Output::write(_escapes[IDX(Esctype::MOVE_LEFT)]);
}

/* move right */
void Xf::Escape::move_right(void) {
	Xf::Output::write(_escapes[IDX(Esctype::MOVE_RIGHT)]);
}


/* erase screen */
void Xf::Escape::erase_screen(void) {
	Xf::Output::write(_escapes[IDX(Esctype::ERASE_SCREEN)]);
}

/* erase line */
void Xf::Escape::erase_line(void) {
	Xf::Output::write(_escapes[IDX(Esctype::ERASE_LINE)]);
}

/* erase to end of line */
void Xf::Escape::erase_to_end(void) {
	Xf::Output::write(_escapes[IDX(Esctype::ERASE_TO_END)]);
}

/* erase from start of line */
void Xf::Escape::erase_from_start(void) {
	Xf::Output::write(_escapes[IDX(Esctype::ERASE_FROM_START)]);
}


/* enter screen */
void Xf::Escape::enter_screen(void) {
	Xf::Output::write(_escapes[IDX(Esctype::ENTER_SCREEN)]);
}

/* exit screen */
void Xf::Escape::exit_screen(void) {
	Xf::Output::write(_escapes[IDX(Esctype::EXIT_SCREEN)]);
}

/* save screen */
void Xf::Escape::save_screen(void) {
	Xf::Output::write(_escapes[IDX(Esctype::SAVE_SCREEN)]);
}

/* restore screen */
void Xf::Escape::restore_screen(void) {
	Xf::Output::write(_escapes[IDX(Esctype::RESTORE_SCREEN)]);
}


/* reset style */
void Xf::Escape::reset_style(void) {
	Xf::Output::write(_escapes[IDX(Esctype::RESET_STYLE)]);
}


/* show cursor */
void Xf::Escape::show_cursor(void) {
	Xf::Output::write(_escapes[IDX(Esctype::SHOW_CURSOR)]);
}

/* hide cursor */
void Xf::Escape::hide_cursor(void) {
	Xf::Output::write(_escapes[IDX(Esctype::HIDE_CURSOR)]);
}

/* request position */
void Xf::Escape::request_position(void) {
	Xf::Output::write(_escapes[IDX(Esctype::REQUEST_POSITION)]);
}


/* cursor beam */
void Xf::Escape::cursor_beam(void) {
	Xf::Output::write(_escapes[IDX(Esctype::CURSOR_BEAM)]);
}

/* cursor underline */
void Xf::Escape::cursor_underline(void) {
	Xf::Output::write(_escapes[IDX(Esctype::CURSOR_UNDERLINE)]);
}

/* cursor block */
void Xf::Escape::cursor_block(void) {
	Xf::Output::write(_escapes[IDX(Esctype::CURSOR_BLOCK)]);
}











#define BUFFER_SIZE_POS			32
#define ZERO_ASCII				48
#define BASE					10
#define ESCAPE_BUFFER_SIZE		64
#define FOREGROUND				true
#define BACKGROUND				false


bool Xf::Escape::request_position(UInt32& x, UInt32& y) {

	UInt32* num     = &y;
	bool    bracket = false;
	char    c       = 0;

	const Xf::CString& esc = _escapes[IDX(Esctype::REQUEST_POSITION)];

	write(STDOUT_FILENO, esc.pointer(), esc.size());
	x = y = 0;
	// iterate while input available
	while (0 < read(STDIN_FILENO, &c, 1) && c != 'R') {
		// check bracket sequence
		if (bracket) {
			// convert character to integer
			if ((c ^ 48) < 10)
				*num = (*num * 10) + (c - 48);
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


/* move position */
void Xf::Escape::move_position(UInt32 x, UInt32 y) {
	Xf::Output::write(get_move_position(x, y));
}

/* get move position */
Xf::CString Xf::Escape::get_move_position(UInt32 x, UInt32 y) {
	UInt8  escape[ESCAPE_BUFFER_SIZE];
	UInt32 ite;

	constexpr const UInt32 max = Xf::max<UInt32>();

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
	return Xf::CString((char*)&escape[ite], ESCAPE_BUFFER_SIZE - ite);
}



// -- C O L O R ---------------------------------------------------------------

/* hex color */
void Xf::Escape::hex_color(const UInt32 color, const bool fore) {
	Xf::Output::write(get_hex_color(color, fore));
}

/* rgb color */
void Xf::Escape::rgb_color(UInt8 r, UInt8 g, UInt8 b, const bool fore) {
	Xf::Output::write(get_rgb_color(r, g, b, fore));
}


/* hex color */
Xf::CString Xf::Escape::get_hex_color(const UInt32 color, const bool fore) {

	// declare bytes color
	UInt8 r, g, b;
	// get color layer
	r = (color >> 16) & 0xFF;
	g = (color >> 8)  & 0xFF;
	b = (color)       & 0xFF;

	return get_rgb_color(r, g, b, fore);
}

/* color rgb */
Xf::CString Xf::Escape::get_rgb_color(UInt8 r, UInt8 g, UInt8 b, const bool fore) {
	// static 24bit color escape sequence
	static UInt8	escape[] = {	'\x1b', '[',
									' ', '8', ';', '2', ';',
									'0', '0', '0', ';',
									'0', '0', '0', ';',
									'0', '0', '0', 'm', '\0'
	};
	constexpr UInt32 r_off = 0x6;
	constexpr UInt32 g_off = 0xA;
	constexpr UInt32 b_off = 0xE;

	// foreground / background char
	escape[2] =  fore == true ? '3' : '4';
	// integer to ascii
	for (UInt32 x = 3; x; --x) {
		// red integer to ascii
		escape[x + r_off] = ((r % BASE) ^ ZERO_ASCII);
		// green integer to ascii
		escape[x + g_off] = ((g % BASE) ^ ZERO_ASCII);
		// blue integer to ascii
		escape[x + b_off] = ((b % BASE) ^ ZERO_ASCII);
		// remove last digit
		r /= BASE; g /= BASE; b /= BASE;
	} // append escape sequence to buffer
	return Xf::CString((char*)escape, 19);
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





// ESC[#A	moves cursor up # lines
// ESC[#B	moves cursor down # lines

// ESC[#E	moves cursor to beginning of next line, # lines down
// ESC[#F	moves cursor to beginning of previous line, # lines up

// ESC[#G	moves cursor to column #
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
