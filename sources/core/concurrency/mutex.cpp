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

#include "xns/concurrency/mutex.hpp"
#include <pthread.h>


// -- public lifecycle --------------------------------------------------------

/* default constructor */
xns::mutex::mutex(void) noexcept
: _mutex PTHREAD_MUTEX_INITIALIZER {
}

/* attribute constructor */
xns::mutex::mutex(const attr& attribute)
: _mutex{} {
	// initialize mutex
	//if (::pthread_mutex_init(&_mutex, &attr._attr) != 0)
	//	throw;
}
