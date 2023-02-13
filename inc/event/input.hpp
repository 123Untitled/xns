#ifndef INPUT_HEADER
#define INPUT_HEADER

#include "terminal.hpp"
#include "types.hpp"
#include "event.hpp"
#include "array.hpp"
#include "string.hpp"

#include <unistd.h>
#include <string>


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- I N P U T  C L A S S ------------------------------------------------

	class Input final {

		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* non-instanciable class */
			NON_INSTANCIABLE(Input);


			// -- S T A T I C  P U B L I C  M E T H O D S ---------------------

			/* start loop */
			static void start_loop(void);

			/* stop input loop */
			static void stop_loop(void);


		private:

			// -- A L I A S E S -----------------------------------------------

			/* string type */
			using String = std::string;

			/* character type */
			using Char = String::value_type;

			/* readed bytes type */
			using Readed = SInt64;

			/* size type */
			using Size = String::size_type;


			// -- S T A T I C  P R I V A T E  M E T H O D S -------------------

			/* read input while available */
			static void read_input(void);

			/* read input from stdin */
			static Readed read_stdin(void);

			/* dispatch to subscribers */
			static void dispatch(void);


			/* filter extended ascii codes */
			static void filter_extended(void);

			/* filter control characters */
			static void filter_control(void);


			// -- P R I V A T E  E N U M S ------------------------------------

			enum { BUFFER_SIZE = 1024 };


			// -- S T A T I C  P R I V A T E  M E M B E R S -------------------

			static String      _input;
			static Char        _buff[BUFFER_SIZE + 1];
			static Readed      _readed;
			static bool        _is_running;

	};

};



#endif
