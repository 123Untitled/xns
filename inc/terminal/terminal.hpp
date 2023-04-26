#ifndef TERM_HEADER
#define TERM_HEADER

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

// xf headers
#include "types.hpp"
#include "macro.hpp"
#include "event.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	enum class VFlag : bool {
		NON_BLOCKING = 0,
		BLOCKING     = 1
	};


	// -- T E R M  C L A S S --------------------------------------------------

	class Term final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* window size type */
			using Wsize = unsigned short;


			// -- C O N S T R U C T O R S -------------------------------------

			/* non-assignable class */
			NON_ASSIGNABLE(Term);

			/* destructor */
			~Term(void);


			// -- M E T H O D S -----------------------------------------------

			/* get singleton instance */
			static Term& instance(void);

			/* set raw terminal */
			void raw_terminal(const VFlag vmin = Xf::VFlag::BLOCKING);

			/* restore original terminal */
			void restore_terminal(void);


			/* flush stdin buffer */
			static void flush(void);


			/* get terminal size */
			static void get_terminal_size(Wsize& width, Wsize& height);


			/* check tty and control terminal */
			static int check_control_term(void);

			/* get process info */
			static void get_process_info(void);


		private:

			// -- A L I A S E S -----------------------------------------------

			/* window size structure type */
			using Winsize = struct winsize;

			/* terminal settings type */
			using Termios = struct termios;


			// -- C O N S T R U C T O R S -------------------------------------

			/* private default constructor */
			Term(void);


			// -- M E T H O D S -----------------------------------------------

			/* get terminal settings */
			const Termios setup_terminal(void);

			/* setup raw terminal */
			void setup_raw(void);

			/* query terminal size */
			static int query_terminal_size(void);

			/* signal handler */
			static void terminal_resize_handler(int signum);



			// -- M E M B E R S -----------------------------------------------

			/* singleton instance */
			static Term _instance;

			// raw terminal flag
			bool _is_raw;

			// original terminal flag
			bool _is_origin;

			// setup flag
			bool _is_setup;

			// original terminal settings
			const Termios _origin;

			// raw terminal settings
			Termios _raw;

			/* terminal width */
			Wsize _width;

			/* terminal height */
			Wsize _height;



	};

};


#endif

