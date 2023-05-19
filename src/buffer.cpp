#include "buffer.hpp"

/* singleton instance */
Xf::Output Xf::Output::_instance = Xf::Output{};

/* default constructor */
Xf::Output::Output(void)
: _buffer{ } {
	// reserve default buffer size
	_buffer.reserve(DEFAULT_BUFFER_SIZE);
}

/* destructor */
Xf::Output::~Output(void) {
	// code here...
}

/* write unknown bytes */
void Xf::Output::write(const char* str) {
	// append to buffer
	_instance._buffer.append(str);
}

/* write bytes */
void Xf::Output::write(const char* str, const xns::cstring::size_type size) {
	// append to buffer
	_instance._buffer.append(str, size);
}

/* write string */
void Xf::Output::write(const xns::cstring& str) {
	// append to buffer
	_instance._buffer.append(str);
}


void Xf::Output::render(const int fd) {

	// check if buffer is empty
	if (_instance._buffer.empty()) { return; }

	// write buffer to file descriptor
	(void)::write(fd, _instance._buffer.pointer(), _instance._buffer.size());

	// clear buffer
	_instance._buffer.clear();
}



///* default constructor */
//Buffer::Buffer(void)
//:	_buff{Allocator::allocate(DEFAULT_BUFFER_SIZE)},
//	_capacity{DEFAULT_BUFFER_SIZE},
//	_size{0},
//	_exit_render{true} {
//	// code here...
//}
//
///* destructor */
//Buffer::~Buffer(void) {
//	// check if buffer is allocated
//	if (_buff) {
//		// render buffer
//		if (_exit_render) { _render(); }
//		// free memory
//		Allocator::deallocate(_buff);
//	}
//}
//
//
///* draw */
//void Buffer::draw(const void* ptr, const Size count) {
//	// get instance
//	Buffer& buffer = get_instance();
//
//	buffer._draw(ptr, count);
//}
//
///* draw */
//void Buffer::_draw(const void* ptr, const Size count) {
//
//	// exit if pointer is null
//	if (!_buff) { return; }
//
//	const Size required = _size + count;
//
//	// extend buffer if required
//	if (required > _capacity) {
//
//		Pointer new_buff = Allocator::realloc(_buff, required);
//
//		// exit, realloc failed
//		if (!new_buff) { return; }
//
//		_buff = new_buff;
//		_capacity = required;
//	}
//
//	// copy data into buffer
//	for (Size x = 0, z = _size; x < count; ++x, ++z) {
//		_buff[z] = ((Pointer)ptr)[x];
//	}
//	// update position
//	_size += count;
//}
//
///* get instance */
//Buffer& Buffer::get_instance(void) {
//	return _instance;
//}
//
///* render */
//void Buffer::render(const int fd) {
//	// get instance
//	Buffer& buffer = get_instance();
//	(void)buffer._render(fd);
//}
//
//void Buffer::render(void) {
//	// get instance
//	Buffer& buffer = get_instance();
//	(void)buffer._render(STDOUT_FILENO);
//}
//
///* [PRIVATE] render */
//int Buffer::_render(const int fd) {
//	int writed = ::write(fd, _buff, _size);
//	_size = 0;
//	return writed;
//}
//
//Buffer Buffer::_instance{};

