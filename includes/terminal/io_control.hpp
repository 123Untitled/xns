#ifndef IO_CONTROL_HEADER
#define IO_CONTROL_HEADER

// local headers
#include "string_literal.hpp"
#include "unique_descriptor.hpp"

// operating system headers
#include <sys/ioctl.h>

#ifndef KERNEL
#define KERNEL /* XXX - FREAD and FWRITE ifdef'd KERNEL*/
#endif
#include <sys/fcntl.h>
#ifdef KERNEL
#undef KERNEL
#endif

#include <termios.h>
#include <unistd.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I O  C O N T R O L  N A M E S P A C E -------------------------------

	namespace io_control {


		/* struct termios type */
		using attrs = struct termios;


		static inline auto stdin(void) -> xns::unique_descriptor& {
			static xns::unique_descriptor _stdin{STDIN_FILENO};
			return _stdin;
		}

		static inline auto stdout(void) -> xns::unique_descriptor& {
			static xns::unique_descriptor _stdout{STDOUT_FILENO};
			return _stdout;
		}

		static inline auto stderr(void) -> xns::unique_descriptor& {
			static xns::unique_descriptor _stderr{STDERR_FILENO};
			return _stderr;
		}


		/* get terminal attributes */
		inline int get_attr(const xns::unique_descriptor& fd,
								  xns::io_control::attrs& term) {

			return ::ioctl(fd.get(), TIOCGETA, &term);
		}




		/* set terminal attributes */
		template <xns::basic_string_literal opt, bool soft = false>
		inline int set_attr(const xns::unique_descriptor& fd, const attrs& term) {

			static_assert(opt == "NOW"
					   || opt == "DRAIN"
					   || opt == "FLUSH",
					   "): SET_ATTR: invalid option :(");

			const attrs* local_term = &term;

			// TCSASOFT: if this value is or'ed into the optional_actions value,
			// the values of the c_cflag, c_ispeed, and c_ospeed fields are ignored.
			if constexpr (soft == true) {
				attrs soft_term;
				soft_term = term;
				soft_term.c_cflag |= CIGNORE;
				local_term = &soft_term;
			}

			// TCSANOW: the change occurs immediately.
			if constexpr (opt == "NOW") {
				return ::ioctl(fd.get(), TIOCSETA, local_term);
			}
			// TCSADRAIN: the change occurs after all output written to fildes has been transmitted to the terminal.
			// This value of optional_actions should be used when changing parameters that affect output.
			else if constexpr (opt == "DRAIN") {
				return ::ioctl(fd.get(), TIOCSETAW, local_term);
			}
			// TCSAFLUSH: the change occurs after all output written to fildes has been transmitted to the terminal.
			// Additionally, any input that has been received but not read is discarded.
			else if constexpr (opt == "FLUSH") {
				return ::ioctl(fd.get(), TIOCSETAF, local_term);
			}
		}

		inline void test() {

			attrs term;

			xns::io_control::set_attr<"NOW">(
					xns::io_control::stdin(),
					term
			);

		}

		// If the process has a controlling terminal,
		// the tcsetpgrp() function sets the foreground process group ID associated with the terminal device to pgid_id.
		// The terminal device associated with fildes
		// must be the controlling terminal of the calling process
		// and the controlling terminal must be currently associated with the session of the calling process.
		 // The value of pgid_id must be the same as the process group ID of a process in the same session as the calling process.

		/* set process group */
		inline int set_process_group(const int fd, const xns::s32 id) {
			return ::ioctl(fd, TIOCSPGRP, &id);
		}

		/* get process group */
		inline pid_t get_process_group(int fd) {
			xns::s32 s;
			if (::ioctl(fd, TIOCGPGRP, &s) < 0)
				return ((pid_t)-1);
			return ((pid_t)s);
		}

		/* get output speed */
		inline ::speed_t get_ospeed(const attrs& term) {
			return term.c_ospeed;
		}

		/* get input speed */
		inline ::speed_t get_ispeed(const attrs& term) {
			return term.c_ispeed;
		}

		/* set output speed */
		inline void set_ospeed(attrs& term, const ::speed_t speed) {
			term.c_ospeed = speed;
		}

		/* set input speed */
		inline void set_ispeed(attrs& term, const ::speed_t speed) {
			term.c_ispeed = speed;
		}

		/* set input and output speed */
		inline void set_speed(attrs& term, const ::speed_t speed) {
			term.c_ispeed = term.c_ospeed = speed;
		}


		inline void make_raw(attrs& term) {

			term.c_iflag &= (unsigned long)~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL|IXON);
			term.c_oflag &= (unsigned long)~OPOST;
			term.c_lflag &= (unsigned long)~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
			term.c_cflag &= (unsigned long)~(CSIZE|PARENB);
			term.c_cflag |= CS8;
			/* XXX set MIN/TIME */
		}


		inline int send_break(const int fd, const int len) {

			struct timeval sleepytime;

			sleepytime.tv_sec = 0;
			sleepytime.tv_usec = 400000;

			if (::ioctl(fd, TIOCSBRK, 0) == -1) { return -1; }

			(void)select(0, 0, 0, 0, &sleepytime);

			if (::ioctl(fd, TIOCCBRK, 0) == -1) { return -1; }

			return 0;
		}

		inline int tcdrain(const int fd) {
			return ::ioctl(fd, TIOCDRAIN, 0);
		}

		template <xns::basic_string_literal action>
		inline int flush(const int fd) {

			static_assert(action == "TCIFLUSH"
					|| action == "TCOFLUSH"
					|| action == "TCIOFLUSH",
					"): TCFUSH: invalid argument :(");

			int com;

			if constexpr (action == "TCIFLUSH") {
				com = FREAD;
			}
			else if constexpr (action == "TCOFLUSH") {
				com = FWRITE;
			}
			else if constexpr (action == "TCIOFLUSH") {
				com = FREAD | FWRITE;
			}
			return ::ioctl(fd, TIOCFLUSH, &com);
		}


		template <xns::basic_string_literal action>
		inline int flow(const int fd) {

			static_assert(action == "TCOOFF"
					|| action == "TCOON"
					|| action == "TCION"
					|| action == "TCIOFF",
					"): TCFLOW: invalid argument :(");

			attrs term;
			xns::ubyte c;
			xns::ubyte _posix_vdisable = static_cast<xns::ubyte>('\377');

			// turn on output data flow
			if constexpr (action == "TCOON") {
				return ::ioctl(fd, TIOCSTART, 0);
			}
			// turn off output data flow
			else if constexpr (action == "TCOOFF") {
				return ::ioctl(fd, TIOCSTOP, 0);
			}
			else if constexpr (action == "TCION" || action == "TCIOFF") {

				if (xns::io_control::get_attr(fd, term) == -1) {
					return -1;
				}

				if constexpr (action == "TCION") {
					c = term.c_cc[VSTART];
				}
				else if constexpr (action == "TCIOFF") {
					c = term.c_cc[VSTOP];
				}

				// check _POSIX_VDISABLE
				if (c == _posix_vdisable) {
					return 0;
				}
				if (write(fd, &c, sizeof(c)) == -1) {
					return -1;
				}
			}
			return 0;

		}

	}

}

#endif // IO_CONTROL_HEADER









