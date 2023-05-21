#include "file.hpp"

xns::file::file(void)
: _file{ }, _path{ }, _fd{ }, _data{ }, _state{false} {
	// code here...
}

/* path constructor */
xns::file::file(const xns::cstring& path)
: _file{}, _path{path}, _fd{}, _data{}, _state{false} {
	// code here...
}

xns::file::~file(void) {
}

void xns::file::open(void) {

	if (_path.empty()) { return; }

	// check file exist
	if (stat(_path.pointer(), &_data) == -1) { return; }

	// check is regular file
	if (!S_ISREG(_data.st_mode)) { return; }

	// check error while opening file
	_fd = xns::unique_fd::make_fd(::open(_path.pointer(), O_RDONLY));

	if (!_fd) { return; }

	_state = true;
	std::cout << "NO ERROR WHILE OPENING FILE: " << _path.pointer() << std::endl;
}

/* get path */
const xns::cstring& xns::file::path(void) const {
	// return file path
	return _path;
}


void xns::file::file_name(xns::cstring&& path) {
	//_path = static_cast<String&&>(path);
}

void xns::file::content(void) {

	if (!_state) { return; }

	_state = false;

	off_t size = _data.st_size;

	_file.reserve(size);

	if (_file.capacity() != (xns::size_t)size) {
		std::cout << "RESERVE FAILED" << std::endl;
		_state = false;
		return;
	}

	// WARNING: need to set size in String class !!!
	if (read(_fd.get(), _file.pointer(), size) != size) {
		_state = false;
		return;
	}

	std::cout << "FILE CORRECTLY READED" << std::endl;
	std::cout << "size: " << size << std::endl;

	write(1, _file.pointer(), size);

}
