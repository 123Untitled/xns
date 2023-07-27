#include "input.hpp"


// -- I N  C L A S S ----------------------------------------------------------


// -- static public methods ---------------------------------------------------

/* read stdin */
xns::in::string xns::in::read(void) {

	in::string input{};
	size_type size{0};
	signed_type readed{0};

	do {
		// resize input
		input.resize(input.size() + BUFFER_SIZE);
		// read stdin
		readed = ::read(STDIN_FILENO, input.data() + size, BUFFER_SIZE);
		// update total size
		size += static_cast<size_type>(readed);

	// loop over stdin
	} while (readed == BUFFER_SIZE);

	if (readed < 0) { /* error */ }

	input.resize(size);

	return input;
}


