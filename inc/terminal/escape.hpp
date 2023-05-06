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
			using Value = Xf::CString;

			/* char type */
			using CharT = Value::CharT;

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
			static const Xf::CString& move_home(void);

			/* move left */
			static const Xf::CString& move_left(void);

			/* move right */
			static const Xf::CString& move_right(void);


			/* erase screen */
			static const Xf::CString& erase_screen(void);

			/* erase line */
			static const Xf::CString& erase_line(void);

			/* erase to end of line */
			static const Xf::CString& erase_to_end(void);

			/* erase from start of line */
			static const Xf::CString& erase_from_start(void);


			/* enter screen */
			static const Xf::CString& enter_screen(void);

			/* exit screen */
			static const Xf::CString& exit_screen(void);

			/* save screen */
			static const Xf::CString& save_screen(void);

			/* restore screen */
			static const Xf::CString& restore_screen(void);


			/* reset style */
			static const Xf::CString& reset_style(void);


			/* show cursor */
			static const Xf::CString& show_cursor(void);

			/* hide cursor */
			static const Xf::CString& hide_cursor(void);

			/* request position */
			static const Xf::CString& request_position(void);


			/* cursor beam */
			static const Xf::CString& cursor_beam(void);

			/* cursor underline */
			static const Xf::CString& cursor_underline(void);

			/* cursor block */
			static const Xf::CString& cursor_block(void);



			// -- S P E C I A L  E S C A P E  S E Q U E N C E S ---------------

			/* request position */
			static bool request_position(TSize&, TSize&);


			/* move position */
			static Xf::CString move_position(TSize, TSize);

			/* move x position */
			static const Xf::CString& move_x(TSize);

			/* move left */
			static Xf::CString move_left(const TSize);

			/* move right */
			static Xf::CString move_right(const TSize);

			/* move up */
			static Xf::CString move_up(const TSize);

			/* move down */
			static Xf::CString move_down(const TSize);

		private:

			/* move direction */
			static Xf::CString _move_direction(TSize, const Char);


		public:

			/* hex color */
			static Xf::CString hex_color(const UInt32, const bool = true);

			/* rgb color */
			static Xf::CString rgb_color(UInt8, UInt8, UInt8, const bool = true);




		private:



			// -- P R I V A T E  S T A T I C  M E M B E R S -------------------

			/* escape sequences */
			static const EscArray _escapes;

	};

}





#endif
