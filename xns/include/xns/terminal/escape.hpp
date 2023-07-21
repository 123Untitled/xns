#ifndef ESCAPE_HEADER
#define ESCAPE_HEADER

#include <unistd.h>
#include <iostream>


#include "types.hpp"
#include "color.hpp"
#include "output.hpp"
#include "macro.hpp"
#include "array.hpp"
#include "string.hpp"
#include "numeric_limits.hpp"

#include "type_traits.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	struct Esctype_def {

		enum Type : xns::size_t {
			/* move */
			MOVE_HOME,
			/* erase */
			ERASE_SCREEN, ERASE_LINE, ERASE_TO_END, ERASE_FROM_START,
			/* screen */
			ENTER_SCREEN, EXIT_SCREEN, SAVE_SCREEN, RESTORE_SCREEN,
			/* color */
			RESET_STYLE,
			/* cursor */
			SHOW_CURSOR, HIDE_CURSOR, REQUEST_POSITION,
			/* cursor style */
			CURSOR_BEAM, CURSOR_UNDERLINE, CURSOR_BLOCK,
			/* max */
			ESCTYPE_MAX
		};
	};


	/* safe enum class */
	template <typename T>
	class SafeEnum : public T {

		private:
			using Type = typename T::Type;
			Type value;

		public:
			SafeEnum(const Type v) : value(v) { }
			Type get(void) const { return value; }
	};

		enum Esctype : xns::size_t {
			/* move */
			MOVE_HOME,
			/* erase */
			ERASE_SCREEN, ERASE_LINE, ERASE_TO_END, ERASE_FROM_START,
			/* screen */
			ENTER_SCREEN, EXIT_SCREEN, SAVE_SCREEN, RESTORE_SCREEN,
			/* color */
			RESET_STYLE,
			/* cursor */
			SHOW_CURSOR, HIDE_CURSOR, REQUEST_POSITION,
			/* cursor style */
			CURSOR_BEAM, CURSOR_UNDERLINE, CURSOR_BLOCK,
			/* max */
			ESCTYPE_MAX
		};

	// -- E S C A P E  T Y P E ------------------------------------------------

	//using Esctype = SafeEnum<Esctype_def>;




	// -- E S C A P E ---------------------------------------------------------

	class escape final {


		private:

			// -- private types -----------------------------------------------

			/* string type */
			using string = xns::string;

			/* character type */
			using char_t = typename string::char_t;

			/* array type */
			using esc_array = xns::array<string, IDX(Esctype::ESCTYPE_MAX)>;

			/* terminal size */
			using term_size = xns::term_size;


		public:

			// -- public constructors -----------------------------------------

			/* non-instantiable class */
			NON_INSTANCIABLE(escape);



			// -- P U B L I C  S T A T I C  M E T H O D S ---------------------

			/* move home */
			static const string& move_home(void);


			/* erase screen */
			static const string& erase_screen(void);

			/* erase line */
			static const string& erase_line(void);

			/* erase to end of line */
			static const string& erase_to_end(void);

			/* erase from start of line */
			static const string& erase_from_start(void);


			/* enter screen */
			static const string& enter_screen(void);

			/* exit screen */
			static const string& exit_screen(void);

			/* save screen */
			static const string& save_screen(void);

			/* restore screen */
			static const string& restore_screen(void);


			/* reset style */
			static const string& reset_style(void);


			/* show cursor */
			static const string& show_cursor(void);

			/* hide cursor */
			static const string& hide_cursor(void);

			/* request position */
			static const string& request_position(void);


			/* cursor beam */
			static const string& cursor_beam(void);

			/* cursor underline */
			static const string& cursor_underline(void);

			/* cursor block */
			static const string& cursor_block(void);



			// -- S P E C I A L  E S C A P E  S E Q U E N C E S ---------------

			/* request position */
			static bool request_position(term_size&, term_size&);


			/* move position */
			static xns::string move_position(term_size, term_size);

			/* move x position */
			static const string& move_x(term_size);

			/* move left */
			static string move_left(const term_size = 1);

			/* move right */
			static string move_right(const term_size = 1);

			/* move up */
			static string move_up(const term_size = 1);

			/* move down */
			static string move_down(const term_size = 1);


		private:

			/* move direction */
			static string _move_direction(term_size, const char_t);


		public:

			/* hex color */
			static string hex_color(const xns::hexcolor, const bool = true);

			/* rgb color */
			static string rgb_color(xns::u8, xns::u8, xns::u8, const bool = true);


		private:

			// -- private static members --------------------------------------

			/* escape sequences */
			static const esc_array _escapes;

	};

}





#endif
