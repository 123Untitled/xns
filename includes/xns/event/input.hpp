/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_INPUT_HEADER
#define XNS_INPUT_HEADER

//#include "xns/terminal.hpp"

// xns headers
#include "xns/type_traits/types.hpp"
#include "xns/containers/array.hpp"
#include "xns/string/string.hpp"
#include "xns/terminal/escape.hpp"
#include "xns/terminal/output.hpp"


// operating system headers
#include <unistd.h>
#include <sys/socket.h>



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
			using char_t = typename string::char_type;

			/* size type */
			using size_type = typename string::size_type;



			// -- public constructors -----------------------------------------

			/* non-instanciable class */
			NON_INSTANCIABLE(in);


			// -- static public methods ---------------------------------------

			/* read descriptor */
			static auto read(const int = STDIN_FILENO) -> string;

			/* recv descriptor */
			static auto recv(const int = STDIN_FILENO) -> string;




		private:


			// -- private enums -----------------------------------------------

			/* buffer size */
			enum { BUFFER_SIZE = 2 };


	};

}

#endif
