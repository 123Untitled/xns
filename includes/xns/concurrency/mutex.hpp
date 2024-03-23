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

#ifndef XNS_MUTEX_HEADER
#define XNS_MUTEX_HEADER

// local headers
#include "xns/config/macros.hpp"

// operating system headers
#include <pthread.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- forward declarations ------------------------------------------------

	/* lock */
	class guard_lock;


	// -- M U T E X -----------------------------------------------------------

	class mutex final {


		// -- friends ---------------------------------------------------------

		/* guard_lock as friend */
		friend class guard_lock;


		public:

			// -- forward declarations ----------------------------------------

			/* attr */
			class attr;


			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::mutex;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			mutex(void) noexcept;

			/* attribute constructor */
			mutex(const attr&);

			/* not assignable */
			XNS_NOT_ASSIGNABLE(mutex);

			/* destructor */
			~mutex(void) noexcept = default; /* need to check how mutex was initialized */


			// -- public classes ----------------------------------------------

			/* attr */
			class attr final {

				// -- friends ---------------------------------------------

				/* mutex as friend */
				friend class mutex;

			}; // class attr


		private:

			// -- private members ---------------------------------------------

			/* mutex */
			::pthread_mutex_t _mutex;

	}; // class mutex

} // namespace xns

#endif // XNS_MUTEX_HEADER
