#include "unique.hpp"

// -- C O N S T R U C T O R S ----------------------------------------------

/* default constructor */
Xf::UniqueFd::UniqueFd(void)
: _fd{NULLFD} {
	// code here...
}

/* file descriptor constructor */
Xf::UniqueFd::UniqueFd(Fd fd)
: _fd{fd} {

	// check if fd is not null
	if (_fd != NULLFD) {

		// reset file descriptor if is not valid
		if (fcntl(_fd, F_GETFD) == -1) {
			_fd = NULLFD;
		}

	}
}

/* move constructor */
Xf::UniqueFd::UniqueFd(UniqueFd&& other) noexcept
: _fd{other._fd} {
	// set other to null
	other._fd = NULLFD;
}

/* destructor */
Xf::UniqueFd::~UniqueFd(void) {
	// check if fd is not null
	if (_fd != NULLFD) {
		// close file descriptor
		std::cout << "CLOSING FD" << std::endl;
		close(_fd);
	}
}


// -- O P E R A T O R S -------------------------------------------

Xf::UniqueFd& Xf::UniqueFd::operator=(UniqueFd&& other) noexcept {

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
Xf::UniqueFd::operator bool(void) const {
	return _fd != NULLFD;
}

/* bool not operator */
bool Xf::UniqueFd::operator!(void) const {
	return _fd == NULLFD;
}


// -- M E T H O D S -----------------------------------------------

/* get file descriptor */
Xf::UniqueFd::Fd Xf::UniqueFd::get(void) const {
	return _fd;
}

/* duplicate */
Xf::UniqueFd Xf::UniqueFd::duplicate(void) const {
	// check if fd is not null
	if (_fd != NULLFD) {
		// duplicate file descriptor
		return UniqueFd{dup(_fd)};
	}
	// return null
	return UniqueFd{};
}

/* duplicate 2 */
void Xf::UniqueFd::duplicate(UniqueFd& other) const {
	// check if fd is not null
	if (_fd != NULLFD) {
		// duplicate file descriptor
		dup2(_fd, other._fd);
	}

}

/* make fd */
Xf::UniqueFd Xf::UniqueFd::make_fd(const Fd fd) {
	return Xf::UniqueFd{fd};
}



