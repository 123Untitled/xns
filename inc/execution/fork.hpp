#ifndef FORK_HPP
#define FORK_HPP

// xns headers
#include "macro.hpp"
#include "remove.hpp"
#include "types.hpp"

// operating system headers
#include <unistd.h>
#include <sys/wait.h>
#include <sys/errno.h>


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
			fork(C& instance, xns::u8 (C::*child)(void), int (C::*parent)(void))
			: _schild{0}, _sparent{0} {


				// fork
				::pid_t pid = ::fork();

				// check for error
				if (pid == -1) {
					_sparent = errno;
				}
				// check for child process
				else if (pid == 0) {

					::_exit((instance.*child)());
				}
				// check for parent process
				else {

					_sparent = (instance.*parent)();

					::waitpid(pid, &_schild, 0);

				}

			}

			/* non-assignable class */
			NON_ASSIGNABLE(fork);

			/* destructor */
			~fork(void) noexcept = default;


			// -- public accessors --------------------------------------------

			/* child status */
			inline status child(void) const noexcept {
				return _schild;
			}

			/* parent status */
			inline status parent(void) const noexcept {
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