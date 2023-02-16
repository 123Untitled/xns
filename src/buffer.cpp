#include "buffer.hpp"


/* [PRIVATE] default constructor */
Buffer::Buffer(void)
:	_buff{Allocator::allocate(DEFAULT_BUFFER_SIZE)},
	_capacity{DEFAULT_BUFFER_SIZE},
	_size{0} {
	// code here...
}

/* [PUBLIC] destructor */
Buffer::~Buffer(void) {
	// free memory
	if (_buff) {
		_render();
		Allocator::deallocate(_buff); }
}

/* [PUBLIC] draw */
void Buffer::draw(const void* ptr, const Size count) {
	// get instance
	Buffer& buffer = get_instance();

	buffer._draw(ptr, count);
}

/* [PRIVATE] draw */
void Buffer::_draw(const void* ptr, const Size count) {

	// exit if pointer is null
	if (!_buff) { return; }

	const Size required = _size + count;

	// extend buffer if required
	if (required > _capacity) {

		Pointer new_buff = Allocator::realloc(_buff, required);

		// exit, realloc failed
		if (!new_buff) { return; }

		_buff = new_buff;
		_capacity = required;
	}

	// copy data into buffer
	for (Size x = 0, z = _size; x < count; ++x, ++z) {
		_buff[z] = ((Pointer)ptr)[x];
	}
	// update position
	_size += count;
}

/* get instance */
Buffer& Buffer::get_instance(void) {
	return _instance;
}

/* render */
int Buffer::render(const int fd) {
	// get instance
	Buffer& buffer = get_instance();

	return buffer._render(fd);
}

/* [PRIVATE] render */
int Buffer::_render(const int fd) {
	int writed = write(fd, _buff, _size);
	_size = 0;
	return writed;
}

Buffer Buffer::_instance{};

