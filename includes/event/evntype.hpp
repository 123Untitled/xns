#ifndef XNS_EVNTYPE_HEADER
#define XNS_EVNTYPE_HEADER

#include "types.hpp"
#include "macros.hpp"

// -- N A M E S P A C E -------------------------------------------------------

namespace xns {


	// -- E V N T Y P E -------------------------------------------------------

	/* enum definition */
	enum evntype : xns::ubyte {
		NUL,          // null character (ctrl+space)
		SOH,          // start of heading (ctrl+a)
		STX,          // start of text (ctrl+b)
		ETX,          // end of text (ctrl+c)
		EOT,          // end of transmission (ctrl+d)
		ENQ,          // enquiry (ctrl+e)
		ACK,          // acknowledge (ctrl+f)
		BEL,          // bell (ctrl+g)
		BS,           // backspace
		HT,           // horizontal tab
		LF,           // line feed
		VT,           // vertical tab
		FF,           // form feed
		CR,           // carriage return
		SO,           // shift out
		SI,           // shift in
		DLE,          // data link escape
		DC1,          // device control 1
		DC2,          // device control 2
		DC3,          // device control 3
		DC4,          // device control 4
		NAK,          // negative acknowledge
		SYN,          // synchronous idle
		ETB,          // end of transmission block
		CAN,          // cancel
		EM,           // end of medium
		SUB,          // substitute
		ESC,          // escape
		FS,           // file separator
		GS,           // group separator
		RS,           // record separator
		US,           // unit separator
		SPACE,        // space
		EXCLAMATION,  // !
		DOUBLE_QUOTE, // "
		HASH,         // #
		DOLLAR,       // $
		PERCENT,      // %
		AMPERSAND,    // &
		SINGLE_QUOTE, // '
		LEFT_PAREN,   // (
		RIGHT_PAREN,  // )
		ASTERISK,     // *
		PLUS,         // +
		COMMA,        // ,
		MINUS,        // -
		PERIOD,       // .
		SLASH,        // /
		ZERO,         // 0
		ONE,          // 1
		TWO,          // 2
		THREE,        // 3
		FOUR,         // 4
		FIVE,         // 5
		SIX,          // 6
		SEVEN,        // 7
		EIGHT,        // 8
		NINE,         // 9
		COLON,        // :
		SEMICOLON,    // ;
		LESS_THAN,    // <
		EQUAL,        // =
		GREATER_THAN, // >
		QUESTION,     // ?
		AT,           // @
		MAJ_A,        // A
		MAJ_B,        // B
		MAJ_C,        // C
		MAJ_D,        // D
		MAJ_E,        // E
		MAJ_F,        // F
		MAJ_G,        // G
		MAJ_H,        // H
		MAJ_I,        // I
		MAJ_J,        // J
		MAJ_K,        // K
		MAJ_L,        // L
		MAJ_M,        // M
		MAJ_N,        // N
		MAJ_O,        // O
		MAJ_P,        // P
		MAJ_Q,        // Q
		MAJ_R,        // R
		MAJ_S,        // S
		MAJ_T,        // T
		MAJ_U,        // U
		MAJ_V,        // V
		MAJ_W,        // W
		MAJ_X,        // X
		MAJ_Y,        // Y
		MAJ_Z,        // Z
		LEFT_BRACKET, // [
		BACKSLASH,    //
		RIGHT_BRACKET,// ]
		CARET,        // ^
		UNDERSCORE,   // _
		BACKQUOTE,    // `
		MIN_A,        // a
		MIN_B,        // b
		MIN_C,        // c
		MIN_D,        // d
		MIN_E,        // e
		MIN_F,        // f
		MIN_G,        // g
		MIN_H,        // h
		MIN_I,        // i
		MIN_J,        // j
		MIN_K,        // k
		MIN_L,        // l
		MIN_M,        // m
		MIN_N,        // n
		MIN_O,        // o
		MIN_P,        // p
		MIN_Q,        // q
		MIN_R,        // r
		MIN_S,        // s
		MIN_T,        // t
		MIN_U,        // u
		MIN_V,        // v
		MIN_W,        // w
		MIN_X,        // x
		MIN_Y,        // y
		MIN_Z,        // z
		LEFT_BRACE,   // {
		PIPE,         // |
		RIGHT_BRACE,  // }
		TILDE,        // ~
		DEL,          // delete

		// escape sequences
		UP,           // \x1b[A
		DOWN,         // \x1b[B
		LEFT,         // \x1b[D
		RIGHT,        // \x1b[C

		// special events
		TERMINAL_RESIZE, // terminal resize

		// enter in mode
		BEGIN,

		// event for each loop
		LOOP,



		EVNT_MAX
	};


}

#endif
