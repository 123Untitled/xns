#include "Buffer.hpp"


#define DEFAULT_BUFFER_SIZE 1024

char*	Buffer::_buff	= initBuffer();
UInt	Buffer::_size	= DEFAULT_BUFFER_SIZE;
UInt	Buffer::_pos	= 0;


/* draw */
void Buffer::draw(const void* ptr, const UInt size) {
	if (_buff) {
		if (_pos + size >= _size)
			extend(size);
		for (UInt x = 0; x < size; ++x) {
			_buff[x + _pos] = ((unsigned char*)ptr)[x];
		}
		_pos += size;
	}
}

/* extend */
void Buffer::extend(const UInt size) {
	// doubles the size until the buffer is large enough
	while ((_pos + size) >= _size) {
		// extend size
		_size *= 2;
	} // new size memory allocation
	char* tmp = new char[_size];
	// iterate over previous allocation content
	for (UInt x = 0; x < _pos; ++x) {
		// copy each bytes to new allocated pointer
		tmp[x] = _buff[x];
	} // free previous allocation memory
	delete _buff;
	// assign new allocation
	_buff = tmp;
}

/* render */
int Buffer::render(const int fd) {

	int writed = write(fd, _buff, _pos);

	_pos = 0;

	return (writed);
}

/* initBuffer */
char* Buffer::initBuffer(void) {
	// record static method for end of program
	std::atexit(&staticDestructor);
	// return buffer default memory allocation
	return (new char[DEFAULT_BUFFER_SIZE]());
}

/* staticDestructor */
void Buffer::staticDestructor(void) {
	// check pointer not null
	if (_buff)
		// free memory
		delete _buff;
}
