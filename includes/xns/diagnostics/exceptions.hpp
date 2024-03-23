/*****************************************************************************/
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*****************************************************************************/

#pragma once

#ifndef XNS_EXCEPTIONS_HEADER
#define XNS_EXCEPTIONS_HEADER

#include "xns/type_traits/types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	/* no exceptions */
	#if defined(__cpp_exceptions) || defined(__EXCEPTIONS)
	/* exceptions enabled */
	constexpr bool no_exceptions = false;
	#else
	/* exceptions disabled */
	constexpr bool no_exceptions = true;
	#endif


	// -- E X C E P T I O N ---------------------------------------------------

	class exception {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::exception;

			/* error code type */
			using code = xns::s32;

			/* error message type */
			using message = const char*;


			// -- constructors ------------------------------------------------

			/* default constructor */
			exception(void) = delete;

			/* copy constructor */
			exception(const self& e) = default;

			/* code and message constructor */
			exception(const code& c, message m) : _code(c), _message(m) {}

			/* destructor */
			virtual ~exception(void) = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			self& operator=(const self& e) = default;


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

} // namespace xns

#endif // XNS_EXCEPTIONS_HEADER
