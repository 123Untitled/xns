#ifndef INPUT_HEADER
#define INPUT_HEADER

//#include "terminal.hpp"
#include "types.hpp"
#include "array.hpp"
#include "string.hpp"
#include "escape.hpp"
#include "output.hpp"

//#include "event.hpp"


#include <unistd.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

//namespace xns {
//
//
//	// -- I N P U T -----------------------------------------------------------
//
//	class input final {
//
//
//		public:
//
//			// -- public types ------------------------------------------------
//
//			/* string type */
//			using string = xns::string;
//
//			/* character type */
//			using char_t = typename string::char_t;
//
//			/* size type */
//			using size_type = typename string::size_type;
//
//			/* signed type */
//			using signed_type = typename string::signed_type;
//
//
//			// -- public constructors -----------------------------------------
//
//			/* non-instanciable class */
//			NON_INSTANCIABLE(input);
//
//
//			// -- S T A T I C  P U B L I C  M E T H O D S ---------------------
//
//			/* start loop */
//			static void start_loop(void);
//
//			/* stop input loop */
//			static void stop_loop(void);
//
//			/* parameters */
//			static void parameters(const bool windowed);
//
//
//		private:
//
//			// -- S T A T I C  P R I V A T E  M E T H O D S -------------------
//
//			/* read input while available */
//			static void read_input(void);
//
//			/* read input from stdin */
//			static signed_type read_stdin(void);
//
//			/* dispatch to subscribers */
//			static void dispatch(void);
//
//
//			// -- P R I V A T E  E N U M S ------------------------------------
//
//			enum { BUFFER_SIZE = 1024 };
//
//
//			// -- S T A T I C  P R I V A T E  M E M B E R S -------------------
//
//			/* input string */
//			static string _input;
//
//			/* buffer */ // TODO: implement resize method in string class
//			static char_t _buff[BUFFER_SIZE + 1];
//
//			/* readed bytes */
//			static signed_type _readed;
//
//
//			static bool _is_running;
//			static bool _windowed;
//
//	};
//
//};



#endif
