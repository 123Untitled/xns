#ifndef INPUT_HEADER
#define INPUT_HEADER

//#include "terminal.hpp"

// xns headers
#include "types.hpp"
#include "array.hpp"
#include "string.hpp"
#include "escape.hpp"
#include "output.hpp"


// operating system headers
#include <unistd.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I N  C L A S S ------------------------------------------------------

	class in final {


		public:

			// -- public types ------------------------------------------------

			/* string type */
			using string = xns::string;

			/* signed type */
			using signed_type = typename string::signed_type;

			/* character type */
			using char_t = typename string::char_t;

			/* size type */
			using size_type = typename string::size_type;



			// -- public constructors -----------------------------------------

			/* non-instanciable class */
			NON_INSTANCIABLE(in);


			// -- static public methods ---------------------------------------

			/* read stdin */
			static string read(void);



		private:


			// -- private enums -----------------------------------------------

			/* buffer size */
			enum { BUFFER_SIZE = 2 };


	};

};



#endif
