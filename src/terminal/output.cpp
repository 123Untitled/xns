#include "buffer.hpp"

/* singleton instance */
xns::output xns::output::_instance = xns::output{};

/* default constructor */
xns::output::output(void)
: _buffer{ } {
	// reserve default buffer size
	_buffer.reserve(DEFAULT_BUFFER_SIZE);
}

/* destructor */
xns::output::~output(void) {
	// code here...
}

/* write unknown bytes */
void xns::output::write(const char* str) {
	// append to buffer
	_instance._buffer.append(str);
}

/* write bytes */
void xns::output::write(const char* str, const xns::cstring::size_type size) {
	// append to buffer
	_instance._buffer.append(str, size);
}

/* write string */
void xns::output::write(const xns::cstring& str) {
	// append to buffer
	_instance._buffer.append(str);
}


