#include "debug.hpp"

int Xf::Debug::initialize(const char* tty) {

	if (!tty) { tty = "/dev/ttys001"; }

	int tmp = open(tty, O_WRONLY);

	if (tmp < 0) { return -1; }

	_tty = tmp;

	print("\n\n\x1b[32mLOG START\x1b[0m\n\n");

	return tmp;
}

void Xf::Debug::write(const void* data, UInt64 size) {
	// exit if no data or tty not open
	if (_tty < 0) { return; }
	if (!data)    { return; }

	if (!size) {
		// if no size, assume null-terminated string
		::write(_tty, data, strlen((const char*)data));
		return;
	}
	::write(_tty, data, size);
}



int Xf::Debug::_tty = initialize();
