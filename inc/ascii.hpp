#ifndef ASCII_HEADER
#define ASCII_HEADER

#include "types.hpp"
#include "macro.hpp"
#include "array.hpp"
#include "string.hpp"
#include "safe_enum.hpp"
#include "literal_map.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A S C I I  C L A S S ------------------------------------------------

	class ascii {

		public:

			// -- T Y P E S ---------------------------------------------------

			/* character type */
			using char_t = char;

			/* const pointer type */
			using const_pointer = const char_t*;

			/* string type */
			using string = xns::string;

			/* size type */
			using size_type = xns::size_t;


			// -- C O N S T A N T S -------------------------------------------

			/* number of printable characters */
			static constexpr size_type printable = 95;

			/* zero character */
			static constexpr char_t zero_ascii = 48;

			/* number of characters */
			static constexpr size_type size = xns::max<char_t>() + 1;

			/* offset to printable characters */
			static constexpr size_type offset = 32;


			// -- C O N S T R U C T O R S -------------------------------------

			/* non-instanciable class */
			NON_INSTANCIABLE(ascii);


			// -- S T A T I C  M E T H O D S ----------------------------------

			//static char_type get_chartype(const char_t c) {
			//	return _table[0];
			//}

		private:

			/* whitespace map */ // 'space', 'tab', 'line feed', 'vertical tab', 'form feed', 'carriage return'
			static constexpr xns::literal_map<char,
							 "space",
							 "tab",
							 "line feed",
							 "vertical tab",
							 "form feed",
							 "carriage return"> _whitespaces {
								 ' ', '\t', '\n', '\v', '\f', '\r'

							 };

			template <class T>
			void test(void) {

				std::cout << _whitespaces.get<"space">() << std::endl;


			}

			struct char_type_def {
				// integral type
				using type = size_type; // need a meta function to get unsigned version of a type
				// enum type
				enum enum_type : type {
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
					LEFT_CURLY, PIPE, RIGHT_CURLY, TILDE,
					MAX
				};
			};

			using char_type = xns::safe_enum<char_type_def>;


			// -- P R I V A T E  T Y P E S ------------------------------------

			/* character table type */
			using char_table = xns::array<char_type, size>;

			/* character info table type */
			using char_info = xns::array<const_pointer, size>;



		private:


			static constexpr const char_table _table {
				char_type::LEFT_CURLY,
				char_type::EXCLAMATION,
				char_type::DOUBLE_QUOTE,
				/* ... */


			};


			static constexpr const char_info _info {
				"Null character",
				"Start of Heading",
				"Start of Text",
				"End of Text",
				"End of Transmission",
				"Enquiry",
				"Acknowledge",
				"Bell, Alert",
				"Backspace",
				"Horizontal Tab",
				"Line Feed",
				"Vertical Tabulation",
				"Form Feed",
				"Carriage Return",
				"Shift Out",
				"Shift In",
				"Data Link Escape",
				"Device Control One (XON)",
				"Device Control Two",
				"Device Control Three (XOFF)",
				"Device Control Four",
				"Negative Acknowledge",
				"Synchronous Idle",
				"End of Transmission Block",
				"Cancel",
				"End of medium",
				"Substitute",
				"Escape",
				"File Separator",
				"Group Separator",
				"Record Separator",
				"Unit Separator",
				"Space",
				"Exclamation mark",
				"Double quotes",
				"Number sign",
				"Dollar",
				"Per cent sign",
				"Ampersand",
				"Single quote",
				"Open parenthesis",
				"Close parenthesis",
				"Asterisk",
				"Plus",
				"Comma",
				"Hyphen-minus",
				"Period, dot or full stop",
				"Slash or divide",

				"Zero", "One", "Two", "Three", "Four", "Five",
				"Six", "Seven", "Eight", "Nine",

				"Colon",
				"Semicolon",
				"Less than",
				"Equals",
				"Greater than",
				"Question mark",
				"At sign",

				"Uppercase A", "Uppercase B", "Uppercase C", "Uppercase D",
				"Uppercase E", "Uppercase F", "Uppercase G", "Uppercase H",
				"Uppercase I", "Uppercase J", "Uppercase K", "Uppercase L",
				"Uppercase M", "Uppercase N", "Uppercase O", "Uppercase P",
				"Uppercase Q", "Uppercase R", "Uppercase S", "Uppercase T",
				"Uppercase U", "Uppercase V", "Uppercase W", "Uppercase X",
				"Uppercase Y", "Uppercase Z",

				"Opening bracket",
				"Backslash",
				"Closing bracket",
				"Circumflex accent",
				"Underscore",
				"Grave accent",

				"Lowercase a", "Lowercase b", "Lowercase c", "Lowercase d",
				"Lowercase e", "Lowercase f", "Lowercase g", "Lowercase h",
				"Lowercase i", "Lowercase j", "Lowercase k", "Lowercase l",
				"Lowercase m", "Lowercase n", "Lowercase o", "Lowercase p",
				"Lowercase q", "Lowercase r", "Lowercase s", "Lowercase t",
				"Lowercase u", "Lowercase v", "Lowercase w", "Lowercase x",
				"Lowercase y", "Lowercase z",

				"Opening brace",
				"Vertical bar",
				"Closing brace",
				"Tilde",
				"Delete"
			};


	};

};




#endif
