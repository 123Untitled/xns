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

#ifndef XNS_GUARD_LOCK_HEADER
#define XNS_GUARD_LOCK_HEADER

#include "concurrency/mutex.hpp"
#include "utility/macros.hpp"

#include <pthread.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- G U A R D  L O C K --------------------------------------------------

	class guard_lock final {

		public:

			// -- public constructor ------------------------------------------

			/* deleted default constructor */
			guard_lock(void) = delete;

			/* mutex constructor */
			inline guard_lock(xns::mutex& mutex)
			: _mutex{mutex} {

				if (::pthread_mutex_lock(&_mutex._mutex) != 0)
					throw;
			}

			/* not assignable */
			XNS_NOT_ASSIGNABLE(guard_lock);

			/* destructor */
			~guard_lock(void) noexcept {

				// unlock mutex
				::pthread_mutex_unlock(&_mutex._mutex);
			}


		private:

			// -- private members ---------------------------------------------

			/* mutex reference */
			xns::mutex& _mutex;

	}; // class guard_lock

} // namespace xns

#endif // XNS_GUARD_LOCK_HEADER
