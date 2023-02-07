#ifndef INPUT_HEADER
#define INPUT_HEADER

#include "Term.hpp"
#include "Types.hpp"
#include "event.hpp"

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


			static void get_event(void);




		private:

			// -- S T A T I C  P R I V A T E  M E T H O D S -------------------

			/* read input from stdin */
			static SInt64 read_stdin(void);

			static void process_input(void);

			static void processEscape(void);
			static void processArrow(void);


			// -- P R I V A T E  E N U M S ------------------------------------

			enum { BUFFER_SIZE = 1024 };


			// -- S T A T I C  P R I V A T E  M E M B E R S -------------------

			static std::string _input;
			static char        _buff[BUFFER_SIZE + 1];
			static SInt64      _readed;
			static bool        _is_running;

	};

};



#endif
