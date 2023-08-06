#include "unique_fd.hpp"

// -- U N I Q U E  F D  C L A S S ---------------------------------------------


// -- public lifecycle --------------------------------------------------------

/* default constructor */
xns::unique_fd::unique_fd(void) noexcept
: _fd{NULLFD} {}

/* file descriptor constructor */
xns::unique_fd::unique_fd(const fd_type fd) noexcept
: _fd{fd} {

	// check if fd is not null
	if (_fd != NULLFD) {

		// reset file descriptor if is not valid
		if (fcntl(_fd, F_GETFD) == -1) {
			_fd = NULLFD;
		}

		// i don't understand this
		/*
		else {
			fcntl(_fd, F_SETFD, FD_CLOEXEC);
		}*/

	}
}

/* move constructor */
xns::unique_fd::unique_fd(unique_fd&& other) noexcept
: _fd{other._fd} {
	// invalidate other file descriptor
	other._fd = NULLFD;
}

/* destructor */
xns::unique_fd::~unique_fd(void) noexcept {
	// check file descriptor
	if (_fd != NULLFD) {
		// close file descriptor
		::close(_fd);
	}
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
xns::unique_fd& xns::unique_fd::operator=(unique_fd&& other) noexcept {
	// check for self assignment
	if (this != &other) {
		// close file descriptor
		if (_fd != NULLFD) { close(_fd); }
		// set fd
		_fd = other._fd;
		// invalidate other file descriptor
		other._fd = NULLFD;
	} // return self reference
	return *this;
}


// -- public boolean operators ------------------------------------------------

/* boolean operator */
xns::unique_fd::operator bool(void) const {
	return _fd != NULLFD;
}

/* not operator */
bool xns::unique_fd::operator!(void) const {
	return _fd == NULLFD;
}


// -- public accessors --------------------------------------------------------

/* valid */
bool xns::unique_fd::valid(void) const noexcept {
	return _fd != NULLFD;
}

/* get file descriptor */
xns::unique_fd::fd_type xns::unique_fd::get(void) const noexcept {
	return _fd;
}



// -- M E T H O D S -----------------------------------------------

/* duplicate */ // deprecated
[[deprecated("not well implemented")]]
xns::unique_fd xns::unique_fd::duplicate(void) const {
	// check if fd is not null
	if (_fd != NULLFD) {
		// duplicate file descriptor
		return unique_fd{dup(_fd)};
	}
	// return null
	return unique_fd{};
}

/* duplicate 2 */
[[deprecated("not well implemented")]]
void xns::unique_fd::duplicate(unique_fd& other) const {
	// check if fd is not null
	if (_fd != NULLFD) {
		// duplicate file descriptor
		dup2(_fd, other._fd);
	}

}



