#ifndef MUTEX_HEADER
#define MUTEX_HEADER

// local headers
#include "macros.hpp"
#include "types.hpp"

// operating system headers
#include <pthread.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- forward declarations ------------------------------------------------

	/* lock */
	class lock;


	// -- M U T E X  C L A S S ------------------------------------------------

	class mutex final {


		// -- friends ---------------------------------------------------------

		/* lock as friend */
		friend class lock;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline mutex(void) noexcept
			: _mutex{}, _state{VALID} {
				// initialize mutex
				if (::pthread_mutex_init(&_mutex, nullptr) != 0) {
					// set invalid
					_state = INVALID;
				}
			}

			/* non-assignable class */
			NON_ASSIGNABLE(mutex);

			/* destructor */
			inline ~mutex(void) noexcept {
				// call lookup
				(this->*_lookup[_state])();
			}


			// -- public accessors --------------------------------------------

			/* valid */
			inline auto valid(void) const noexcept -> bool {
				return _state == VALID;
			}


		private:

			// -- private methods ---------------------------------------------

			/* empty method */
			inline auto nope(void) noexcept -> void {}

			/* destroy mutex */
			inline auto destroy(void) noexcept -> void {
				if (::pthread_mutex_destroy(&_mutex) != 0) {
					/* error... */ }
			}

			// -- private constants -------------------------------------------

			enum state : xns::u8 {
				INVALID = 0x00,
				VALID   = 0x01
			};


			// -- private members ---------------------------------------------

			/* mutex */
			::pthread_mutex_t _mutex;

			/* state */
			state _state;


			// -- private static members --------------------------------------

			/* lookup table */
			static constexpr void(mutex::*_lookup[2])(void) {
				&mutex::nope,
				&mutex::destroy
			};

	};

}

#endif // MUTEX_HEADER



