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


	// -- E N U M S ---------------------------------------------------

	enum class Esctype {

		// -- M O V E -------------------------------------------------

		MOVE_HOME, MOVE_LEFT, MOVE_RIGHT,

		// -- E R A S E -----------------------------------------------

		ERASE_SCREEN,
		ERASE_LINE,
		ERASE_TO_END_OF_LINE,
		// ERASE_START_OF_LINE_TO_CURSOR,

		// -- S C R E E N ---------------------------------------------

		ENTER_SCREEN, EXIT_SCREEN, SAVE_SCREEN, RESTORE_SCREEN,

		// -- C O L O R -----------------------------------------------

		RESET_STYLE,

		// -- C U R S O R ---------------------------------------------

		SHOW_CURSOR, HIDE_CURSOR, REQUEST_POSITION,

		// -- C U R S O R  S T Y L E ----------------------------------

		CURSOR_BEAM, CURSOR_UNDERLINE, CURSOR_BLOCK,

		// -- M A X ---------------------------------------------------

		ESCTYPE_MAX
	};


	// -- E S C A P E  S E Q U E N C E S  C L A S S E S ---------------

	#define MAKE_CLASS(NAME, ESC) \
	struct NAME final { \
	static constexpr const Esctype type = Esctype::ESC; \
	}

	/* move home */
	MAKE_CLASS(move_home_t,        MOVE_HOME);

	/* move left */
	MAKE_CLASS(move_left_t,        MOVE_LEFT);

	/* move right */
	MAKE_CLASS(move_right_t,       MOVE_RIGHT);

	/* erase screen */
	MAKE_CLASS(erase_screen_t,     ERASE_SCREEN);

	/* erase line */
	MAKE_CLASS(erase_line_t,       ERASE_LINE);

	/* erase to end of line */
	MAKE_CLASS(erase_to_end_t,     ERASE_TO_END_OF_LINE);

	/* enter screen */
	MAKE_CLASS(enter_screen_t,     ENTER_SCREEN);

	/* exit screen */
	MAKE_CLASS(exit_screen_t,      EXIT_SCREEN);

	/* save screen */
	MAKE_CLASS(save_screen_t,      SAVE_SCREEN);

	/* restore screen */
	MAKE_CLASS(restore_screen_t,   RESTORE_SCREEN);

	/* reset style */
	MAKE_CLASS(reset_style_t,      RESET_STYLE);

	/* show cursor */
	MAKE_CLASS(show_cursor_t,      SHOW_CURSOR);

	/* hide cursor */
	MAKE_CLASS(hide_cursor_t,      HIDE_CURSOR);

	/* cursor beam */
	MAKE_CLASS(cursor_beam_t,      CURSOR_BEAM);

	/* cursor underline */
	MAKE_CLASS(cursor_underline_t, CURSOR_UNDERLINE);

	/* cursor block */
	MAKE_CLASS(cursor_block_t,     CURSOR_BLOCK);


	#undef MAKE_CLASS


	// -- E S C A P E  S E Q U E N C E S  F U N C T I O N S -----------

	struct rgb_color_t {};
	struct hex_color_t {};
	struct move_position_t {};



	// -- E S C A P E  M E T A ----------------------------------------

	/* is escape false */
	template <typename T>
	struct is_escape final : Xf::false_t {};

	/* is escape true */
	template <>
	struct is_escape<Esctype> : Xf::true_t {};

	/* is escape true */
	template <>
	struct is_escape<const Esctype> : Xf::true_t {};

	/* get type of member */
	template <typename E>
	using member = is_escape<decltype(E::type)>;

	/* is escape concept */
	template <typename T>
	concept is_escape_c = is_escape<decltype(T::type)>::value;





	struct hex_color_t;
	struct rgb_color_t;
	struct move_position_t;

	/* is dyn escape false */
	template <typename T>
	struct is_dyn_escape : Xf::false_t {};

	/* is dyn escape true */
	template <>
	struct is_dyn_escape<rgb_color_t> : Xf::true_t {};

	/* is dyn escape true */
	template <>
	struct is_dyn_escape<hex_color_t> : Xf::true_t {};

	/* is dyn escape true */
	template <>
	struct is_dyn_escape<move_position_t> : Xf::true_t {};


	/* is dyn escape concept */
	template <typename T>
	concept is_dyn_escape_c = is_dyn_escape<T>::value;




	// -- E S C A P E  C L A S S ----------------------------------------------

	class Escape final {

		private:

		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* non-instantiable class */
			NON_INSTANCIABLE(Escape);


			// -- S T A T I C  M E T H O D S ----------------------------------


			/* get escape sequence */
			template <is_escape_c E>
			static const Xf::String<char>& get(void) {
				// return escape sequence
				return _escapes[IDX(Esctype(E::type))];
			}

			/* draw escape sequence */
			template <is_escape_c E>
			static void draw(void) {
				// draw escape sequence
				Buffer::draw(_escapes[IDX(E::type)].pointer(),
						_escapes[IDX(E::type)].size());
			}

			/* get special escape */
			template <is_dyn_escape_c E, typename... A>
			static
			Xf::String<char>
			get(A&&... arguments) {
				if constexpr (Xf::is_same_v<E, move_position_t>) {
					// move position
					return _move_position(Xf::forward<A>(arguments)...);
				}
				else if constexpr (Xf::is_same_v<E, hex_color_t>) {
					// hex color
					return _hex_color(Xf::forward<A>(arguments)...);
				}
				else if constexpr (Xf::is_same_v<E, rgb_color_t>) {
					// rgb color
					return _rgb_color(Xf::forward<A>(arguments)...);
				}
				//return E::call(Xf::forward<A>(arguments)...);
			}

			///* draw special escape */
			template <is_dyn_escape_c E, typename... A>
			static void draw(A&&... arguments) {
				Xf::String<char> esc;
				if constexpr (Xf::is_same_v<E, move_position_t>) {
					// move position
					esc = _move_position(Xf::forward<A>(arguments)...);
				}
				else if constexpr (Xf::is_same_v<E, hex_color_t>) {
					// hex color
					esc = _hex_color(Xf::forward<A>(arguments)...);
				}
				else if constexpr (Xf::is_same_v<E, rgb_color_t>) {
					// rgb color
					esc = _rgb_color(Xf::forward<A>(arguments)...);
				}
				// get private escape sequence index
				//esc = E::call(Xf::forward<A>(arguments)...);
				Buffer::draw(esc.pointer(), esc.size());
			}

			/* request cursor position */
			static bool request_position(UInt32& x, UInt32& y);


		private:


			/* hex color */
			static Xf::String<char> _hex_color(const UInt32 color, const bool fore = true);

			/* color rgb */
			static Xf::String<char> _rgb_color(UInt8 r, UInt8 g, UInt8 b, const bool fore = true);

			/* move position */
			static Xf::String<char> _move_position(UInt32 x, UInt32 y);


			// -- M E M B E R S -----------------------------------------------

			/* escape sequences */
			static const Array<String<char>, IDX(Esctype::ESCTYPE_MAX)> _escapes;


		public:



	};


};



#endif
