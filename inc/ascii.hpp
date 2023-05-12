#ifndef ASCII_HEADER
#define ASCII_HEADER

#include "types.hpp"
#include "macro.hpp"
#include "array.hpp"

#include <string>
#include <climits>

#define ZERO_ASCII		48
#define BASE			10

#define WHITE_SPACE		"\x09\x0a\x0b\x0c\x0d\x20"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- A S C I I  C L A S S ------------------------------------------------

	class Ascii {

		public:

			enum Chartype : SizeT {

				SPACE, EXCLAMATION, DOUBLE_QUOTE,
				HASHTAG, DOLLAR, PERCENT,
				AMPERSAND, SINGLE_QUOTE,
				LEFT_PARENTHESIS, RIGHT_PARENTHESIS,
				ASTERISK, PLUS, COMMA, MINUS,
				PERIOD, SLASH, NUMBER, COLON,
				SEMICOLON, LESS, EQUALITY,
				GREATER, QUESTION, AT, LETTER,
				LEFT_SQUARE, BACKSLASH, RIGHT_SQUARE,
				CIRCUMFLEX, UNDERSCORE, ACCENT,
				LEFT_CURLY, PIPE, RIGHT_CURLY, TILDE

			};

			// -- A L I A S E S -----------------------------------------------

			/* character type */
			using CharT = char;

			/* string type */
			using String = std::string;

			/* size type */
			using Size = UInt64;



			static Chartype chartype(const CharT c) {
				return _array[c - OFFSET];
			}

			// -- C O N S T R U C T O R S -------------------------------------

			/* non-instanciable class */
			NON_INSTANCIABLE(Ascii);

		private:

			enum : SizeT {
				OFFSET      = 32,
				LOOKUP_SIZE = 95
			};

			using Chartable = Xf::Array<Chartype, LOOKUP_SIZE>;

			static Chartable _array;

	};

};




#endif
