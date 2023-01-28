
#include <File.hpp>

File::File(void)
: _fd{0} {
	// File default constructor
}

File::File(const Str& path)
: _path{path} {
}

File::~File(void) {
	close(_fd);
}

int File::openFile(void) {
	if (!_path.getPointer())
		return (ERROR);
	// check file exist
	if (!stat(_path.getPointer(), &_data)
		// check is regular file
		&& S_ISREG(_data.st_mode)
		// check error while opening file
		&& (_fd = open(_path.getPointer(), O_RDONLY)) != -1) {
		// catch file content
		if (!catchFile())
			return (NOERR);
	} return (ERROR);
}

const Str& File::getPath(void) const {
	// return file path
	return (_path);
}

void File::print(void) {
	_file.print();
}

void File::setFileName(Str&& path) {
	_path = static_cast<Str&&>(path);
}

int File::catchFile(void) {
	// catch file content
	char		buff[FILE_BUFFER_SIZE + 1] = { 0 };
	SInt64		readed = 0;
	Strlst		lst{};
	// run over file
	while ((readed = read(_fd, buff, FILE_BUFFER_SIZE)) > 0)
		// add buffer to rear linked list
		lst.addBack({buff, static_cast<UInt32>(readed)});
	// check read error
	if (readed == -1) return (ERROR);
	// linked list concatenation
	_file = lst.release();
	// return success
	return (NOERR);
}
