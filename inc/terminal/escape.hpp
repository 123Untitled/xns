#ifndef ESCAPE_HEADER
#define ESCAPE_HEADER


// local headers
#include "types.hpp"
#include "color.hpp"
#include "output.hpp"
#include "macro.hpp"
#include "array.hpp"
#include "string.hpp"
#include "numeric_limits.hpp"

// operating system headers
#include <unistd.h>



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- E S C A P E  T Y P E ------------------------------------------------

	struct esctype_def {
		// integral type
		using type = xns::u8;
		// enum type
		enum enum_type : type {
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
			MAX
		};
	};

	using esctype = xns::safe_enum<esctype_def>;



	// -- E S C A P E ---------------------------------------------------------

	class escape final {


		private:

			// -- private types -----------------------------------------------

			/* string type */
			using string = xns::string;

			/* string view type */
			using view = xns::string_view;

			/* character type */
			using char_t = typename string::char_t;

			/* array type */
			using esc_array = xns::array<view, esctype::size()>;

			/* terminal size */
			using term_size = xns::term_size;


		public:

			// -- public lifecycle --------------------------------------------

			/* non-instantiable class */
			NON_INSTANCIABLE(escape);



			// -- public static methods ---------------------------------------

			/* move home */
			static const view& move_home(void);


			/* erase screen */
			static const view& erase_screen(void);

			/* erase line */
			static const view& erase_line(void);

			/* erase to end of line */
			static const view& erase_to_end(void);

			/* erase from start of line */
			static const view& erase_from_start(void);


			/* enter screen */
			static const view& enter_screen(void);

			/* exit screen */
			static const view& exit_screen(void);

			/* save screen */
			static const view& save_screen(void);

			/* restore screen */
			static const view& restore_screen(void);


			/* reset style */
			static const view& reset_style(void);


			/* show cursor */
			static const view& show_cursor(void);

			/* hide cursor */
			static const view& hide_cursor(void);

			/* request position */
			static const view& request_position(void);


			/* cursor beam */
			static const view& cursor_beam(void);

			/* cursor underline */
			static const view& cursor_underline(void);

			/* cursor block */
			static const view& cursor_block(void);



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
			static constexpr esc_array _escapes {

				/* move home */
				"\x1b[H",

				/* erase screen */
				"\x1b[2J",
				/* erase line */
				"\x1b[2K",
				/* erase to end of line */
				"\x1b[0K",
				/* erase from start of line */
				"\x1b[1K",

				/* enter screen */
				"\x1b[?1049h",
				/* exit screen */
				"\x1b[?1049l",
				/* save screen */
				"\x1b[?47h",
				/* restore screen */
				"\x1b[?47l",

				/* reset style */
				"\x1b[0m",

				/* show cursor */
				"\x1b[?25h",
				/* hide cursor */
				"\x1b[?25l",
				/* request position */
				"\x1b[6n",

				/* cursor beam */
				"\x1b[5 q",
				/* cursor underline */
				"\x1b[3 q",
				/* cursor block */
				"\x1b[1 q"

			};

	};

}





#endif
