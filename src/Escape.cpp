#include "Escape.hpp"


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
