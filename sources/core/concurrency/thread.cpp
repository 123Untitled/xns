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

#include "xns/concurrency/thread.hpp"
#include "xns/utility/swap.hpp"


// -- public lifecycle --------------------------------------------------------

/* default constructor */
xns::thread::thread(void) noexcept
: _thread{} {
}

/* move constructor */
xns::thread::thread(self&& other) noexcept
: _thread{other._thread} {
	other._thread = thread_type{};
}

/* destructor */
xns::thread::~thread(void) noexcept {
	if (_thread != 0)
		::pthread_detach(_thread);
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto xns::thread::operator=(self&& other) noexcept -> self& {

	if (this == &other)
		return *this;

	// check if this thread is not null
#if defined(__MVS__)
	//if (_thread.__ != 0)
#else
	//if (_thread != 0)
#endif
	// terminate()

	_thread = other._thread;
	other._thread = thread_type{};

	return *this;
}


// -- public methods ----------------------------------------------------------

/* join */
auto xns::thread::join(void) noexcept -> void {
	::pthread_join(_thread, nullptr);
	_thread = thread_type{};
}

/* detach */
auto xns::thread::detach(void) noexcept -> void {
	::pthread_detach(_thread);
}

/* swap */
auto xns::thread::swap(self& other) noexcept -> void {

	xns::swap(_thread, other._thread);
}


// -- public accessors --------------------------------------------------------

/* joinable */
auto xns::thread::joinable(void) const noexcept -> bool {
#if defined(__MVS__)
	return _thread.__ != 0;
#else
	return _thread != 0;
#endif
}

/* native_handle */
auto xns::thread::native_handle(void) const noexcept -> const thread_type& {
	return _thread;
}

