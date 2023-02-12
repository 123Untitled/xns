#include "Buffer.hpp"


/* [PRIVATE] default constructor */
Buffer::Buffer(void)
:	_buff{Allocator::allocate(DEFAULT_BUFFER_SIZE)},
	_size{DEFAULT_BUFFER_SIZE},
	_pos{0} {
	// code here...
}

/* [PUBLIC] destructor */
Buffer::~Buffer(void) {
	// free memory
	if (_buff) { Allocator::deallocate(_buff); }
}

/* [PUBLIC] draw */
void Buffer::draw(const void* ptr, const Size count) {
	// get instance
	static Buffer& buffer = get_instance();

	// exit if pointer is null
	if (!buffer._buff) { return; }

	if (buffer._pos + count >= buffer._size) {
		// INFO: need replace this by std::realloc
		Pointer new_buff = Allocator::realloc(buffer._buff, count);

		// exit, realloc failed
		if (!new_buff) { return; }

		buffer._buff = new_buff;
		buffer._size += count;
	}

	// copy data into buffer
	for (Size x = 0, z = buffer._pos; x < count; ++x, ++z) {
		buffer._buff[z] = ((Pointer)ptr)[x];
	}
	// update position
	buffer._pos += count;
}

/* get instance */
Buffer& Buffer::get_instance(void) {
	return _instance;
}

/* render */
int Buffer::render(const int fd) {
	// get instance
	static Buffer& buffer = get_instance();

	int writed = write(fd, buffer._buff, buffer._pos);

	buffer._pos = 0;

	return writed;
}

Buffer Buffer::_instance{};

