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
#include "types.hpp"
#include "macros.hpp"
#include "event.hpp"
#include "is_unsigned.hpp"
#include "output.hpp"

#include "declval.hpp"

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	enum class VFlag : bool {
		NON_BLOCKING = 0,
		BLOCKING     = 1
	};


	// -- T E R M  C L A S S --------------------------------------------------

	class terminal final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::terminal;

			/* terminal size type */
			using term_size = decltype(xns::declval<struct winsize>().ws_row);


			// -- C O N S T R U C T O R S -------------------------------------

			/* non-assignable class */
			unassignable(terminal);

			/* destructor */
			~terminal(void) noexcept;


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
				static_assert(xns::is_unsigned_integral<T>
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

			/* private default constructor */
			terminal(void);


			// -- M E T H O D S -----------------------------------------------

			/* get terminal settings */
			const struct termios setup_terminal(void);

			/* setup raw terminal */
			void setup_raw(void);

			/* query terminal size */
			int query_terminal_size(void);



			/* signal handler */
			static void terminal_resize_handler(int signum);



			// -- private members --------------------------------------------

			/* raw terminal flag */
			bool _is_raw;

			/* original terminal flag */
			bool _is_origin;

			// setup flag
			bool _is_setup;

			// original terminal settings
			const struct termios _origin;

			// raw terminal settings
			struct termios _raw;

			/* terminal width */
			term_size _width;

			/* terminal height */
			term_size _height;



	};

}


#endif

