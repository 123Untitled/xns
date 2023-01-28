#ifndef ASCII_HEADER
#define ASCII_HEADER

#define ZERO_ASCII		48
#define BASE			10

#define WHITE_SPACE		"\x09\x0a\x0b\x0c\x0d\x20"

//#define ESC				'\x1B'	// Escape character			\e ^[
#define BEL				'\x07'	// Terminal bell			\a ^G
#define BS				'\x08'	// Backspace				\b ^H

// White space
#define HT				'\x09'	// Horizontal tab			\t ^I
#define LF				'\x0A'	// Linefeed (newline)		\n ^J
#define VT				'\x0B'	// Vertical tab				\v ^K
#define FF				'\x0C'	// Formfeed (New page NP)	\f ^L
#define CR				'\x0D'	// Carriage return			\r ^M
#define SP				'\x20'	// Space

#define DEL				'\x7F'	// Delete character

#endif
