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

#ifndef XNS_EXCEPTIONS_HEADER
#define XNS_EXCEPTIONS_HEADER

#include "xns/type_traits/types.hpp"
#include "xns/config/config.hpp"


#if XNS_HAS_NOEXCEPT == false


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- E X C E P T I O N ---------------------------------------------------

	class exception {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::exception;

			/* code type */
			using code_type = xns::s32;


			// -- constructors ------------------------------------------------

			/* default constructor */
			exception(void) noexcept
			: _message{"unknown exception"}, _code{0} {
			}

			/* code and message constructor */
			exception(const char* const message, const code_type code) noexcept
			: _message{message}, _code{code} {
			}

			/* copy constructor */
			exception(const self&) noexcept = default;

			/* move constructor */
			exception(self&&) noexcept = default;

			/* destructor */
			virtual ~exception(void) = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public interface --------------------------------------------

			/* what */
			virtual auto what(void) const noexcept -> const char* {
				return _message;
			}


			// -- public methods ----------------------------------------------

			/* code */
			auto code(void) const noexcept -> code_type {
				return _code;
			}

			/* message */
			auto message(void) const noexcept -> const char* {
				return _message;
			}


		private:

			// -- private members ---------------------------------------------

			/* message */
			const char* _message;

			/* code */
			code_type _code;

	}; // class exception

} // namespace xns

#endif // XNS_HAS_EXCEPTIONS

#endif // XNS_EXCEPTIONS_HEADER
