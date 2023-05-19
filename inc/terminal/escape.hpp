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

	struct Esctype_def {

		enum Type : UInt {
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

		enum Esctype : SizeT {
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





	// -- E S C A P E  C L A S S ----------------------------------------------

	class Escape final {


		private:

			// -- P R I V A T E  A L I A S E S --------------------------------


			/* value type */
			using Value = xns::cstring;

			/* char type */
			using CharT = Value::char_t;

			/* reference type */
			using Reference = Value&;

			/* const reference type */
			using ConstRef = const Value&;

			/* array type */
			using EscArray = Xf::Array<Value, IDX(Esctype::ESCTYPE_MAX)>;



		public:


			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* non-instantiable class */
			NON_INSTANCIABLE(Escape);


			// -- P U B L I C  S T A T I C  M E T H O D S ---------------------

			/* move home */
			static const xns::cstring& move_home(void);


			/* erase screen */
			static const xns::cstring& erase_screen(void);

			/* erase line */
			static const xns::cstring& erase_line(void);

			/* erase to end of line */
			static const xns::cstring& erase_to_end(void);

			/* erase from start of line */
			static const xns::cstring& erase_from_start(void);


			/* enter screen */
			static const xns::cstring& enter_screen(void);

			/* exit screen */
			static const xns::cstring& exit_screen(void);

			/* save screen */
			static const xns::cstring& save_screen(void);

			/* restore screen */
			static const xns::cstring& restore_screen(void);


			/* reset style */
			static const xns::cstring& reset_style(void);


			/* show cursor */
			static const xns::cstring& show_cursor(void);

			/* hide cursor */
			static const xns::cstring& hide_cursor(void);

			/* request position */
			static const xns::cstring& request_position(void);


			/* cursor beam */
			static const xns::cstring& cursor_beam(void);

			/* cursor underline */
			static const xns::cstring& cursor_underline(void);

			/* cursor block */
			static const xns::cstring& cursor_block(void);



			// -- S P E C I A L  E S C A P E  S E Q U E N C E S ---------------

			/* request position */
			static bool request_position(TSize&, TSize&);


			/* move position */
			static xns::cstring move_position(TSize, TSize);

			/* move x position */
			static const xns::cstring& move_x(TSize);

			/* move left */
			static xns::cstring move_left(const TSize = 1);

			/* move right */
			static xns::cstring move_right(const TSize = 1);

			/* move up */
			static xns::cstring move_up(const TSize = 1);

			/* move down */
			static xns::cstring move_down(const TSize = 1);

		private:

			/* move direction */
			static xns::cstring _move_direction(TSize, const Char);


		public:

			/* hex color */
			static xns::cstring hex_color(const UInt32, const bool = true);

			/* rgb color */
			static xns::cstring rgb_color(UInt8, UInt8, UInt8, const bool = true);




		private:



			// -- P R I V A T E  S T A T I C  M E M B E R S -------------------

			/* escape sequences */
			static const EscArray _escapes;

	};

}





#endif
