#include "output.hpp"

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

/* new line */
void xns::output::newline(void) {
	// append to buffer
	_instance._buffer += '\n';
}

/* write unknown bytes */
void xns::output::write(const char* str) {
	// append to buffer
	_instance._buffer.append(str);
}

/* write bytes */
void xns::output::write(const char* str, const xns::size_t size) {
	// append to buffer
	_instance._buffer.append(str, size);
}

/* write string */
void xns::output::write(const xns::string& str) {
	// append to buffer
	_instance._buffer.append(str);
}

/* write string32 */
void xns::output::write(const xns::string32& str) {
	// append to buffer
	_instance._buffer.append(xns::char32_to<char>(str));
}












