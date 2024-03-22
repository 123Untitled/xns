#include "event/input.hpp"


// -- I N  C L A S S ----------------------------------------------------------


// -- static public methods ---------------------------------------------------

/* read descriptor */
auto xns::in::read(const int descriptor) -> string {

	in::string  input  { };
	signed_type readed {0};
	size_type   size   {0};

	do {
		// resize input
		input.resize(input.size() + BUFFER_SIZE);
		// read stdin
		readed = ::read(descriptor, input.data() + size, BUFFER_SIZE);

		if (readed < 0) {
			// error
			break;
		}

		// update total size
		size += static_cast<size_type>(readed);

	// loop over stdin
	} while (readed == BUFFER_SIZE);

	if (readed < 0) { /* error */ }

	input.resize(size);

	return input;
}

/* recv descriptor */
auto xns::in::recv(const int descriptor) -> string {

	in::string  input  { };
	signed_type readed {0};
	size_type   size   {0};

	do {
		// resize input
		input.resize(input.size() + BUFFER_SIZE);
		// read stdin
		readed = ::recv(descriptor, input.data() + size, BUFFER_SIZE, 0);

		if (readed < 0) {
			// error
			break;
		}

		// update total size
		size += static_cast<size_type>(readed);

	// loop over stdin
	} while (readed == BUFFER_SIZE);

	if (readed < 0) { /* error */ }

	input.resize(size);

	return input;
}




