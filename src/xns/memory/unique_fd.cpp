#include "unique_fd.hpp"

// -- C O N S T R U C T O R S ----------------------------------------------

/* default constructor */
xns::unique_fd::unique_fd(void)
: _fd{NULLFD} {
	// code here...
}

/* file descriptor constructor */
xns::unique_fd::unique_fd(const fd fd)
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
	// set other to null
	other._fd = NULLFD;
}

/* destructor */
xns::unique_fd::~unique_fd(void) {
	// check if fd is not null
	if (_fd != NULLFD) {
		// close file descriptor
		std::cout << "CLOSING FD" << std::endl;
		close(_fd);
	}
}


// -- O P E R A T O R S -------------------------------------------

xns::unique_fd& xns::unique_fd::operator=(unique_fd&& other) noexcept {

	// check for self assignment
	if (this != &other) {

		// close file descriptor
		if (_fd != NULLFD) { close(_fd); }

		// set fd
		_fd = other._fd;

		// set other to null
		other._fd = NULLFD;

	}

	// return self reference
	return *this;
}

/* bool operator */
xns::unique_fd::operator bool(void) const {
	return _fd != NULLFD;
}

/* bool not operator */
bool xns::unique_fd::operator!(void) const {
	return _fd == NULLFD;
}


// -- M E T H O D S -----------------------------------------------

/* get file descriptor */
xns::unique_fd::fd xns::unique_fd::get(void) const {
	return _fd;
}

/* duplicate */
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
void xns::unique_fd::duplicate(unique_fd& other) const {
	// check if fd is not null
	if (_fd != NULLFD) {
		// duplicate file descriptor
		dup2(_fd, other._fd);
	}

}

/* make fd */
xns::unique_fd xns::unique_fd::make_fd(const fd fd) {
	return xns::unique_fd{fd};
}



