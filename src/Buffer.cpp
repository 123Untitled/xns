#include "Buffer.hpp"


#define DEFAULT_BUFFER_SIZE 1024

char* Buffer::_buff	= initialize_buffer();
UInt  Buffer::_size	= DEFAULT_BUFFER_SIZE;
UInt  Buffer::_pos	= 0;


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

/* initialize buffer */
char* Buffer::initialize_buffer(void) {
	// clean memory allocation at exit
	std::atexit(&static_destructor);
	// return new allocated memory
	return (new char[DEFAULT_BUFFER_SIZE]());
}

/* static destructor */
void Buffer::static_destructor(void) {
	// check if buffer is allocated
	if (_buff) {
		// free memory
		delete[] _buff;
		// reset buffer pointer
		_buff = nullptr;
	}
}
