#include "output.hpp"

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
	::write(STDOUT_FILENO, "write char*\n", 13);
	// append to buffer
	_instance._buffer.append(str);
}

/* write bytes */
void xns::out::write(const char* str, const xns::size_t size) {
	::write(STDOUT_FILENO, "write char*, size_t\n", 20);
	// append to buffer
	_instance._buffer.append(str, size);
}

/* write string */
void xns::out::write(const xns::string& str) {
	::write(STDOUT_FILENO, "write xns::string\n", 18);
	// append to buffer
	_instance._buffer.append(str);
}

/* write string view */
void xns::out::write(const xns::string_view& str) {
	::write(STDOUT_FILENO, "write xns::string_view\n", 23);
	// append to buffer
	_instance._buffer.append(str);
}

/* write string32 */
void xns::out::write(const xns::string32& str) {
	::write(STDOUT_FILENO, "write xns::string32\n", 20);
	// append to buffer
	_instance._buffer.append(xns::char32_to<char>(str));
}












