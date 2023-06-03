#ifndef EXCEPTIONS_HEADER
#define EXCEPTIONS_HEADER

#include "types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- E X C E P T I O N ---------------------------------------------------

	class exception {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = exception;

			/* error code type */
			using code = xns::s32;

			/* error message type */
			using message = const char*;


			// -- constructors ------------------------------------------------

			/* default constructor */
			exception(void) = default;

			/* code and message constructor */
			exception(const code& c, const message& m) : _code(c), _message(m) {}

			/* destructor */
			virtual ~exception(void) = default;


			// -- public methods ----------------------------------------------

			/* get error code */
			code get_code(void) const { return _code; }

			/* get error message */
			message get_message(void) const { return _message; }


		private:

			// -- private members ---------------------------------------------

			/* error code */
			code _code;

			/* error message */
			message _message;


	};

}

#endif
