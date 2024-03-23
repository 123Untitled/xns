#ifndef XNS_FORK_HEADER
#define XNS_FORK_HEADER

// xns headers
#include "xns/macros.hpp"
#include "xns/remove.hpp"
#include "xns/types.hpp"

// operating system headers
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- F O R K -------------------------------------------------------------

	class fork final {


		public:

			// -- public types ------------------------------------------------

			/* status type */
			using status = int;


			// -- public constructors -----------------------------------------

			/* deleted default constructor */
			fork(void) = delete;

			/* default constructor */
			template <class C>
			fork(C& instance, xns::u8 (C::*child_f)(void), int (C::*parent_f)(void))
			: _schild{0}, _sparent{0} {


				// fork
				::pid_t pid = ::fork();

				// check for error
				if (pid == -1) {
					_sparent = errno;
				}
				// check for child process
				else if (pid == 0) {

					::_exit((instance.*child_f)());
				}
				// check for parent process
				else {

					_sparent = (instance.*parent_f)();

					::waitpid(pid, &_schild, 0);

				}

			}

			/* non-assignable class */
			NON_ASSIGNABLE(fork);

			/* destructor */
			~fork(void) noexcept = default;


			// -- public accessors --------------------------------------------

			/* child status */
			inline auto child(void) const noexcept -> status {
				return _schild;
			}

			/* parent status */
			inline auto parent(void) const noexcept -> status {
				return _sparent;
			}


		private:

			// -- private members ---------------------------------------------


			/* child status */
			status _schild;

			/* parent status */
			status _sparent;


	};

}

#endif
