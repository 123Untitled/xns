#include "xns/terminal/output.hpp"

// -- private static methods --------------------------------------------------

/* shared */
auto xns::out::shared(void) -> ___self& {
	static ___self ___ins;
	return ___ins;
}


/* default constructor */
xns::out::out(void)
: _buffer{} {
	// reserve default buffer size
	_buffer.reserve(DEFAULT_BUFFER_SIZE);
}


/* new line */
void xns::out::newline(void) {
	// append to buffer
	___self::shared()._buffer.append('\n');
}

/* write unknown bytes */
void xns::out::write(const char* str) {
	// append to buffer
	___self::shared()._buffer.append(str);
}

/* write bytes */
void xns::out::write(const char* str, const xns::size_t size) {
	// append to buffer
	___self::shared()._buffer.append(xns::string_view{str, size});
}

/* write string */
void xns::out::write(const xns::string& str) {
	// append to buffer
	___self::shared()._buffer.append(str);
}

/* write string view */
void xns::out::write(const xns::string_view& str) {
	// append to buffer
	___self::shared()._buffer.append(str);
}

/* write string32 */
void xns::out::write(const xns::u32string& str) {
	// append to buffer
	___self::shared()._buffer.append(xns::char32_to<char>(str));
}












