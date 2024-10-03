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

#ifndef XNS_TERMINAL_HEADER
#define XNS_TERMINAL_HEADER

// c++ headers
#include <iostream>
#include <list>
#include <csignal>

// system headers
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <fcntl.h>

// xns headers
#include "xns/type_traits/types.hpp"
#include "xns/config/macros.hpp"
#include "xns/event/event.hpp"
#include "xns/type_traits/type_properties/is_unsigned.hpp"
#include "xns/terminal/output.hpp"

#include "xns/type_traits/type_operations/declval.hpp"

#include "xns/diagnostics/exceptions.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	enum class VFlag : bool {
		NON_BLOCKING = 0,
		BLOCKING     = 1
	};



	// -- T E R M I N A L -----------------------------------------------------

	class terminal final {


		public:

			// -- public classes ----------------------------------------------


			class attribute final {


				private:

					// -- private types ---------------------------------------

					/* self type */
					using ___self = xns::terminal::attribute;

					/* tcflag type */
					using ___flag = ::tcflag_t;

					/* cc type */
					using ___cc   = ::cc_t;

					/* termios type */
					using ___termios = struct ::termios;


					// -- private members ---------------------------------------------

					/* attribute */
					___termios _attrs;


				public:

					// -- public lifecycle --------------------------------------------

					/* default constructor */
					attribute(void) noexcept
					/* : _attrs{} no init */ {
					}

					/* copy constructor */
					attribute(const ___self&) noexcept = default;

					/* move constructor */
					attribute(___self&&) noexcept = default;

					/* destructor */
					~attribute(void) noexcept = default;


					// -- public assignment operators ---------------------------------

					/* copy assignment operator */
					auto operator=(const ___self&) noexcept -> ___self& = default;

					/* move assignment operator */
					auto operator=(___self&&) noexcept -> ___self& = default;


					// -- public modifiers --------------------------------------------

					/* raw */
					auto raw(void) noexcept -> void {

						// disable input flags
						_attrs.c_iflag &= ~static_cast<___flag>(
								BRKINT |  IGNBRK | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON | IGNCR);

						// disable output flags
						_attrs.c_oflag &= ~static_cast<___flag>(
								OPOST);

						// disable control flags
						_attrs.c_lflag &= ~static_cast<___flag>(
								ECHO | ECHONL | ICANON | IEXTEN | ISIG);

						// disable local flags
						_attrs.c_cflag &= ~static_cast<___flag>(
								CSIZE | PARENB);
					}


					/* read timeout */
					auto read_timeout(const ___cc& ___time) noexcept -> void {
						_attrs.c_cc[VMIN] = ___time;
					}

					/* min read */
					auto min_read(const ___cc& ___min) noexcept -> void {
						_attrs.c_cc[VTIME] = ___min;
					}


					/* set */
					auto set(const int ___ac) const -> void {

						// set terminal attributes
						if (::tcsetattr(STDIN_FILENO, ___ac, &_attrs) == -1)
							throw xns::exception("failed to set terminal attributes", errno);
					}

					/* get */
					auto get(void) -> void {

						// get terminal attributes
						if (::tcgetattr(STDIN_FILENO, &_attrs) == -1)
							throw xns::exception("failed to get terminal attributes", errno);
					}

			}; // class attribute



			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::terminal;

			/* terminal size type */
			using term_size = decltype(xns::declval<struct ::winsize>().ws_row);


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = xns::terminal;


			// -- private members ---------------------------------------------

			/* original terminal settings */
			const ___self::attribute _origin;

			/* raw terminal settings */
			___self::attribute _raw;

			/* terminal width */
			term_size _width;

			/* terminal height */
			term_size _height;


		public:

			// -- public lifecycle --------------------------------------------


			/* non-assignable class */
			unassignable(terminal);



			// -- M E T H O D S -----------------------------------------------

			/* instance */
			static inline auto shared(void) -> xns::terminal& {
				static self instance{};
				return instance;
			}

			/* set raw terminal */
			static void raw(const VFlag vmin = xns::VFlag::BLOCKING);

			/* restore original terminal */
			static void restore(void);


			/* flush stdin buffer */
			static void flush(void);


			/* get terminal size */
			template <typename T>
			static inline auto terminal_size(T& width, T& height) -> void {

				// require unsigned integral type
				// supporting at least term_size bits
				static_assert(xns::is_unsigned<T> && xns::is_integral<T>
						&& sizeof(T) >= sizeof(term_size),
						"): TERMINAL SIZE TYPE MUST BE UNSIGNED INTEGRAL TYPE :(");

				// get instance
				auto& instance = self::shared();

				width  = static_cast<T>(instance._width);
				height = static_cast<T>(instance._height);
			}

			/* get terminal width */
			static inline auto width(void) -> term_size {
				return self::shared()._width;
			}


			/* check tty and control terminal */
			static int check_control_term(void);

			/* get process info */
			static void get_process_info(void);


		private:

			// -- private lifecycle -------------------------------------------

			/* default constructor */
			terminal(void);

			/* destructor */
			~terminal(void) noexcept;


			// -- private methods ---------------------------------------------

			/* query terminal size */
			auto _query_terminal_size(void) noexcept -> void;


			// -- private static methods --------------------------------------

			/* resize handler */
			static void _resize_handler(const int) noexcept;

	}; // class terminal

} // namespace xns

#endif // XNS_TERMINAL_HEADER
