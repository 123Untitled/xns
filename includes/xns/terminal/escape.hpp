/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_ESCAPE_HEADER
#define XNS_ESCAPE_HEADER


// local headers
#include "xns/type_traits/types.hpp"
#include "xns/color/color.hpp"
#include "xns/terminal/output.hpp"
#include "xns/config/macros.hpp"
#include "xns/containers/array.hpp"
#include "xns/string/string.hpp"
#include "xns/utility/numeric_limits.hpp"

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
			using size_type = xns::size_t;


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
			static bool request_position(size_type&, size_type&);


			/* move position */
			static xns::string move_position(size_type, size_type);

			/* move x position */
			static const string& move_x(size_type);

			/* move left */
			static string move_left(const size_type = 1);

			/* move right */
			static string move_right(const size_type = 1);

			/* move up */
			static string move_up(const size_type = 1);

			/* move down */
			static string move_down(const size_type = 1);


		private:

			/* move direction */
			static string _move_direction(size_type, const char_t);


		public:

			/* hex color */
			static string hex_color(const xns::hexcolor, const bool = true);

			/* rgb color */
			static string rgb_color(xns::u8, xns::u8, xns::u8, const bool = true);

			/* rgb color */
			static string rgb_color(const xns::rgb&, const bool = true);


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




			class req_pos final {

				public:

					static bool request(size_type& x, size_type& y) {

						// create request
						req_pos req{x, y};


						// return success
						return true;
					}



				private:

					// -- private enums ---------------------------------------

					//enum : size_type {
					//	BASE = 10,
					//	ZERO = 48
					//};

					// -- private lifecycle -----------------------------------

					/* size constructor */
					req_pos(size_type& x, size_type& y)
					: _state{nullptr}, _c{0}, _n{&y}, _x{x}, _y{y} {
					};

					/* destructor */
					~req_pos(void) = default;

					bool escape(void) {
						return _c == '\x1b'
							? _state = &req_pos::bracket, true
							: false;
					}

					bool bracket(void) {
						return _c == '['
							? _state = &req_pos::number, true
							: false;
					}

					bool number(void) {
						if ((_c ^ 48) < 10) {
							*_n = (*_n * 10) + (static_cast<size_type>(_c) - 48);
							return true;
						}
						else if (_c == ';') {
							_n = &_x;
							return true;
						}
						return false;
					}

					using proto = bool(req_pos::*)(void);


					// -- private members -------------------------------------

					proto _state;

					/* current character */
					char _c;

					/* current number */
					size_type* _n;

					/* x position */
					size_type& _x;

					/* y position */
					size_type& _y;



			};




	};

}





#endif
