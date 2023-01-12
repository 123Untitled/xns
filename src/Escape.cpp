#include "Escape.hpp"

#include <iostream>
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



SInt32 Escape::resetColor(void) {
	return (write(STDOUT_FILENO, "\x1b[0m", 4));
}

Esc Escape::set24bitColor(const UInt32 color, const bool fore) {
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
	} // send escape sequence to standard output
	//return (write(STDOUT_FILENO, escape, 19));

	return (Esc{escape, sizeof(escape)});
}



SInt32 Escape::moveLeft(void) {
	return (write(STDOUT_FILENO, "\x1b[1D", 4));
}

SInt32 Escape::moveRight(void) {
	return (write(STDOUT_FILENO, "\x1b[1C", 4));
}

SInt32 Escape::movePos(UInt32 x, UInt32 y) {
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
	// send escape sequence to standard output
	return (write(STDOUT_FILENO, &escape[ite], ESCAPE_BUFFER_SIZE - ite));
}


Esc Escape::movePosEsc(UInt32 x = 0, UInt32 y = 0) {
	#define BUFF_SIZE 128
	// static iterator declaration
	static UInt64	ite;
	// static buffer declaration
	static UInt8	escape[BUFF_SIZE + 1];
	// constant characters initialization
	//{ [BUFF_SIZE - 1] = 'H', [BUFF_SIZE] = '\0' };
	escape[BUFF_SIZE - 1] = 'H';
	escape[BUFF_SIZE] = '\0';
	// init iterator
	ite = BUFF_SIZE - 1;
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
	// return static buffer at start position
	return (Esc{&escape[ite], BUFF_SIZE - ite});
}



// CURSOR //////////////////////////
// make cursor invisible
SInt32 Escape::noCursor(void) {
	return (write(STDOUT_FILENO,
			NO_CURSOR,
			sizeof(NO_CURSOR)));
}
// make cursor visible
SInt32 Escape::showCursor(void) {
	return (write(STDOUT_FILENO,
			SHOW_CURSOR,
			sizeof(SHOW_CURSOR)));
}

SInt32 Escape::cursorBeam(void) {
	return (write(STDOUT_FILENO,
			CURSOR_BEAM,
			sizeof(CURSOR_BEAM)));
}

SInt32 Escape::cursorUnderline(void) {
	return (write(STDOUT_FILENO,
			CURSOR_UNDERLINE,
			sizeof(CURSOR_UNDERLINE)));
}

SInt32 Escape::cursorBlock(void) {
	return (write(STDOUT_FILENO,
			CURSOR_BLOCK,
			sizeof(CURSOR_BLOCK)));
}

SInt32 Escape::eraseFromCursorToEOL(void) {
	return (write(STDOUT_FILENO,
			ERASE_FROM_CURSOR_TO_EOL,
			sizeof(ERASE_FROM_CURSOR_TO_EOL)));
}

SInt32 Escape::moveHome(void) {
	return (write(STDOUT_FILENO,
			MOVE_HOME,
			sizeof(MOVE_HOME)));
}

SInt32 Escape::clearScreen(void) {
	return (write(STDOUT_FILENO,
			ERASE_SCREEN,
			sizeof(ERASE_SCREEN)));
}

// enables the alternative buffer
SInt32 Escape::enterScreen(void) {
	return (write(STDOUT_FILENO,
			ENTER_SCREEN,
			sizeof(ENTER_SCREEN)));
}

// disables the alternative buffer
SInt32 Escape::exitScreen(void) {
	return (write(STDOUT_FILENO,
			EXIT_SCREEN,
			sizeof(EXIT_SCREEN)));
}




Esc::Esc(void)
: _ptr{nullptr}, _size{0} {

}

Esc::Esc(const UInt8* ptr, const UInt64 size)
: _ptr{ptr}, _size{size} {

}

Esc::Esc(const Esc& copy)
: _ptr{copy._ptr}, _size{copy._size} {

}

Esc::~Esc(void) {

};

Esc& Esc::operator=(const Esc& assign) {
	_ptr	= assign._ptr;
	_size	= assign._size;
	return (*this);
}

const UInt8* Esc::ptr(void) const {
	return (_ptr);
}

UInt64 Esc::size(void) const {
	return (_size);
}




