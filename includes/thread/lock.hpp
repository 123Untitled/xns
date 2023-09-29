#ifndef LOCK_HEADER
#define LOCK_HEADER

// local headers
#include "mutex.hpp"
#include "macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- L O C K  C L A S S --------------------------------------------------

	class lock final {

		public:

			// -- public constructor ------------------------------------------

			/* deleted default constructor */
			lock(void) = delete;

			/* mutex constructor */
			inline lock(mutex& mutex) noexcept
			: _mutex{mutex} {
				// call lookup
				(this->*_lookup[LOCK][_mutex._state])();
			}

			/* non-assignable class */
			NON_ASSIGNABLE(lock);

			/* destructor */
			inline ~lock(void) noexcept {
				// call lookup
				(this->*_lookup[UNLOCK][_mutex._state])();
			}


		private:

			// -- private methods ---------------------------------------------

			/* empty method */
			inline auto nope(void) noexcept -> void {}

			/* lock mutex */
			inline auto locker(void) noexcept -> void {
				if (::pthread_mutex_lock(&_mutex._mutex) != 0) {
					/* error... */ }
			}

			/* unlock mutex */
			inline auto unlocker(void) noexcept -> void {
				if (::pthread_mutex_unlock(&_mutex._mutex) != 0) {
					/* error... */ }
			}


			// -- private constants -------------------------------------------

			/* method types */
			enum : xns::u8 { LOCK = 0x00, UNLOCK = 0x01 };


			// -- private members ---------------------------------------------

			/* mutex reference */
			xns::mutex& _mutex;


			// -- private static members --------------------------------------

			/* lookup table */
			static constexpr void(lock::*_lookup[2][2])(void) noexcept = {
				{&lock::nope, &lock::locker},
				{&lock::nope, &lock::unlocker}
			};

	};

}

#endif // LOCK_HEADER
