#ifndef ESCAPE_HEADER
#define ESCAPE_HEADER

#include <unistd.h>
#include <iostream>


#include "types.hpp"
#include "color.hpp"
#include "buffer.hpp"
#include "macro.hpp"
#include "array.hpp"
#include "string.hpp"
#include "numeric_limits.hpp"

#include "type_traits.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- E N U M S -----------------------------------------------------------

	enum class Esctype {

		// -- M O V E ---------------------------------------------------------

		MOVE_HOME, MOVE_LEFT, MOVE_RIGHT,

		// -- E R A S E -------------------------------------------------------

		ERASE_SCREEN, ERASE_LINE, ERASE_TO_END, ERASE_FROM_START,

		// -- S C R E E N -----------------------------------------------------

		ENTER_SCREEN, EXIT_SCREEN, SAVE_SCREEN, RESTORE_SCREEN,

		// -- C O L O R -------------------------------------------------------

		RESET_STYLE,

		// -- C U R S O R -----------------------------------------------------

		SHOW_CURSOR, HIDE_CURSOR, REQUEST_POSITION,

		// -- C U R S O R  S T Y L E ------------------------------------------

		CURSOR_BEAM, CURSOR_UNDERLINE, CURSOR_BLOCK,

		// -- M A X -----------------------------------------------------------

		ESCTYPE_MAX
	};


	// -- E S C A P E  C L A S S ----------------------------------------------

	class Escape final {

		public:

			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* non-instantiable class */
			NON_INSTANCIABLE(Escape);


			// -- P U B L I C  S T A T I C  M E T H O D S ---------------------

			/* get escape sequence */
			static const Xf::CString& get(const Esctype);


			/* move home */
			static void move_home(void);

			/* move left */
			static void move_left(void);

			/* move right */
			static void move_right(void);


			/* erase screen */
			static void erase_screen(void);

			/* erase line */
			static void erase_line(void);

			/* erase to end of line */
			static void erase_to_end(void);

			/* erase from start of line */
			static void erase_from_start(void);


			/* enter screen */
			static void enter_screen(void);

			/* exit screen */
			static void exit_screen(void);

			/* save screen */
			static void save_screen(void);

			/* restore screen */
			static void restore_screen(void);


			/* reset style */
			static void reset_style(void);


			/* show cursor */
			static void show_cursor(void);

			/* hide cursor */
			static void hide_cursor(void);

			/* request position */
			static void request_position(void);


			/* cursor beam */
			static void cursor_beam(void);

			/* cursor underline */
			static void cursor_underline(void);

			/* cursor block */
			static void cursor_block(void);



			// -- S P E C I A L  E S C A P E  S E Q U E N C E S ---------------

			/* request position */
			static bool request_position(UInt32&, UInt32&);

			/* move position */
			static void move_position(UInt32, UInt32);

			/* hex color */
			static void hex_color(const UInt32, const bool = true);

			/* rgb color */
			static void rgb_color(UInt8, UInt8, UInt8, const bool = true);


			/* get move position */
			static Xf::CString get_move_position(UInt32, UInt32);

			/* get hex color */
			static Xf::CString get_hex_color(const UInt32, const bool = true);

			/* get rgb color */
			static Xf::CString get_rgb_color(UInt8, UInt8, UInt8, const bool = true);




		private:

			// -- P R I V A T E  A L I A S E S --------------------------------

			/* array type */
			using Array = Xf::Array<Xf::CString, IDX(Esctype::ESCTYPE_MAX)>;


			// -- P R I V A T E  S T A T I C  M E M B E R S -------------------

			/* escape sequences */
			static const Array _escapes;

	};

}




			/* get escape sequence */
			//template <is_escape_c E>
			//static const Xf::String<char>& get(void) {
			//	// return escape sequence
			//	return _escapes[IDX(Esctype(E::type))];
			//}

			///* draw escape sequence */
			//template <is_escape_c E>
			//static void draw(void) {
			//	// draw escape sequence
			//	Buffer::draw(_escapes[IDX(E::type)].pointer(),
			//			_escapes[IDX(E::type)].size());
			//}

			///* get special escape */
			//template <is_dyn_escape_c E, typename... A>
			//static
			//Xf::String<char>
			//get(A&&... arguments) {
			//	if constexpr (Xf::is_same_v<E, move_position_t>) {
			//		// move position
			//		return _move_position(Xf::forward<A>(arguments)...);
			//	}
			//	else if constexpr (Xf::is_same_v<E, hex_color_t>) {
			//		// hex color
			//		return _hex_color(Xf::forward<A>(arguments)...);
			//	}
			//	else if constexpr (Xf::is_same_v<E, rgb_color_t>) {
			//		// rgb color
			//		return _rgb_color(Xf::forward<A>(arguments)...);
			//	}
			//	//return E::call(Xf::forward<A>(arguments)...);
			//}

			/////* draw special escape */
			//template <is_dyn_escape_c E, typename... A>
			//static void draw(A&&... arguments) {
			//	Xf::String<char> esc;
			//	if constexpr (Xf::is_same_v<E, move_position_t>) {
			//		// move position
			//		esc = _move_position(Xf::forward<A>(arguments)...);
			//	}
			//	else if constexpr (Xf::is_same_v<E, hex_color_t>) {
			//		// hex color
			//		esc = _hex_color(Xf::forward<A>(arguments)...);
			//	}
			//	else if constexpr (Xf::is_same_v<E, rgb_color_t>) {
			//		// rgb color
			//		esc = _rgb_color(Xf::forward<A>(arguments)...);
			//	}
			//	// get private escape sequence index
			//	//esc = E::call(Xf::forward<A>(arguments)...);
			//	Buffer::draw(esc.pointer(), esc.size());
			//}

			///* request cursor position */
			//static bool request_position(UInt32& x, UInt32& y);


//		private:
//
//
//			/* hex color */
//			static Xf::String<char> _hex_color(const UInt32 color, const bool fore = true);
//
//			/* color rgb */
//			static Xf::String<char> _rgb_color(UInt8 r, UInt8 g, UInt8 b, const bool fore = true);
//
//			/* move position */
//			static Xf::String<char> _move_position(UInt32 x, UInt32 y);
//
//
//
//
//		public:
//
//
//
//	};
//
//
//};



#endif
