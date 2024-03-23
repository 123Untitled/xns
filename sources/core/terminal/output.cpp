#include "xns/terminal/output.hpp"

/* singleton instance */
xns::out xns::out::_instance = xns::out{};

/* default constructor */
xns::out::out(void)
: _buffer{ } {
	// reserve default buffer size
	_buffer.reserve(DEFAULT_BUFFER_SIZE);
}

/* destructor */
xns::out::~out(void) {
	// code here...
}

/* new line */
void xns::out::newline(void) {
	// append to buffer
	_instance._buffer += '\n';
}

/* write unknown bytes */
void xns::out::write(const char* str) {
	// append to buffer
	_instance._buffer.append(str);
}

/* write bytes */
void xns::out::write(const char* str, const xns::size_t size) {
	// append to buffer
	_instance._buffer.append(str, size);
}

/* write string */
void xns::out::write(const xns::string& str) {
	// append to buffer
	_instance._buffer.append(str);
}

/* write string view */
void xns::out::write(const xns::string_view& str) {
	// append to buffer
	_instance._buffer.append(str);
}

/* write string32 */
void xns::out::write(const xns::u32string& str) {
	// append to buffer
	_instance._buffer.append(xns::char32_to<char>(str));
}












