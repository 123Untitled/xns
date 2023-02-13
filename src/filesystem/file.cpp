#include "file.hpp"

File::File(void)
: _fd{0} {
	// File default constructor
}

File::File(const String& path)
: _path{path} {
}

File::~File(void) {
	close(_fd);
}

int File::openFile(void) {
	if (!_path.pointer())
		return (-1);
	// check file exist
	if (!stat(_path.pointer(), &_data)
		// check is regular file
		&& S_ISREG(_data.st_mode)
		// check error while opening file
		&& (_fd = open(_path.pointer(), O_RDONLY)) != -1) {
		// catch file content
		if (!catchFile())
			return (0);
	} return (-1);
}

const String& File::getPath(void) const {
	// return file path
	return (_path);
}

void File::print(void) {
	_file.print_string();
}

void File::setFileName(String&& path) {
	_path = static_cast<String&&>(path);
}

int File::catchFile(void) {
	// catch file content
	char		buff[FILE_BUFFER_SIZE + 1] = { 0 };
	SInt64		readed = 0;
	LString		lst{};
	// run over file
	while ((readed = read(_fd, buff, FILE_BUFFER_SIZE)) > 0)
		// add buffer to rear linked list
		lst.add_back({buff, static_cast<UInt32>(readed)});
	// check read error
	if (readed == -1) return (-1);
	// linked list concatenation
	_file = lst.merge();
	// return success
	return (0);
}
