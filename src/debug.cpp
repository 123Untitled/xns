#include "debug.hpp"

xns::unique_fd xns::debug::initialize(void) noexcept {

	/*
	if (!tty) { tty = "/dev/ttys001"; }

	int tmp = ::open(tty, O_WRONLY);

	if (tmp < 0) { return -1; }

	_tty = tmp;

	print("\n\n\x1b[32mLOG START\x1b[0m\n\n");

	return tmp;
	return -1;
	*/

	// create new file descriptor
	return xns::unique_fd{xns::string{"debug.log"}, O_WRONLY | O_CREAT | O_TRUNC, 0666};
}


xns::unique_fd xns::debug::_tty = initialize();
