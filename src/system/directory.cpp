#include "directory.hpp"

//Directory::Directory(void)
//: _absolute{}, _directory{nullptr}, _content{}, _isopen{false} {
//	_absolute.reserve(MAXPATHLEN);
//}
//
///* copy constructor */
//Directory::Directory(const Directory& other)
//: Directory{} {
//}
//
///* copy assignment operator */
//Directory& Directory::operator=(const Directory& other)
//{
//	return *this;
//}
//
//Directory::~Directory(void) {
//	deallocation();
//}
//
//bool Directory::isRelative(const String& path) {
//	return (path.front() != C_SLASH ? true : false);
//}
//
//bool Directory::isSlashTerminated(const String& path) {
//	return (path.back() == C_SLASH ? true : false);
//}
//
//void Directory::makeAbsolute(String& path) {
//	static char buff[MAXPATHLEN];
//
//	if (isRelative(path) && getcwd(buff, MAXPATHLEN) != nullptr)
//		path = String{buff} + String{S_SLASH} + path;
//}
//
//
////std::vector<std::list>
//
//void Directory::simplify(String& path) {
//
//	std::list<String> lst;
//
//	String	directory;
//	xns::size_t	size = path.length();
//	for (xns::size_t x = 0; x < size; x++) {
//		directory.clear();
//		while (x < size && path[x] != C_SLASH)
//			directory.push_back(path[x++]);
//		if (directory == S_BACK) {
//			if (lst.size()) lst.pop_back(); }
//		else if (!directory.empty()
//			&& directory != ".")
//			lst.push_back(directory);
//	}
//	path.clear();
//	for (auto ite = lst.begin(); ite != lst.end(); ite++)
//		path += S_SLASH + *ite;
//	path.push_back(C_SLASH);
//}
//
//
//
//
//void Directory::deallocation(void) {
//	if (_directory)
//		closedir(_directory);
//}
//
//void Directory::clearDirectory(void) {
//	for (xns::size_t x = 0; x < TYPE_N; x++)
//		_content[x].clear();
//}
//
//
//void Directory::reset(void) {
//	deallocation();
//	clearDirectory();
//	_directory	= nullptr;
//	_isopen		= false;
//}
//
//
//bool Directory::isOpen(void) const {
//	return (_isopen);
//}
//
//const char* Directory::getDirectoryPath(void) const {
//	return (_absolute.c_str());
//}
//
//Directory::Err Directory::createDirectory(const String& path) {
//	return ((makeDirectory(path)
//		|| openDir(path)) ? ERROR : NOERR);
//}
//
//Directory::Err Directory::makeDirectory(const String& path) {
//	return (mkdir(path.c_str(), 0755) == -1 ? ERROR : NOERR);
//}
//
//Directory::Err Directory::openDir(const String& path) {
//	// check null pointer
//	if (path.length()) {
//		// reset previous opening
//		reset();
//		// assign path to private member
//		_absolute = path;
//		// make absolute path if relative
//		makeAbsolute(_absolute);
//		// try to open directory
//		if ((_directory = opendir(_absolute.c_str()))) {
//			// set flag ok to search in directory
//			_isopen = true;
//			// clean path
//			simplify(_absolute);
//			// get folder content
//			getDirectoryContent();
//			// return success
//			return (NOERR);
//		} // else return error
//	} return (ERROR);
//}
//
//
//void Directory::removeDots(void) {
//	auto ite = _content[T_DIR].begin();
//	while (ite != _content[T_DIR].end()) {
//		if (!(ite->getName().compare(".."))
//			|| !(ite->getName().compare(".")))
//			_content[T_DIR].erase(ite);
//		ite++;
//	}
//}
//
//void Directory::getDirectoryContent(void) {
//
//	const Dirent* file = nullptr;
//	if (_isopen) {
//		while ((file = readdir(_directory))) {
//			Typeindex i = getTypentity(file->d_type);
//
//			_content[i].push_back(DirEntity{_absolute, file});
//		} rewinddir(_directory);
//		removeDots();
//	}
//}
//
//const List<DirEntity>& Directory::getContent(const Typeindex type) const {
//	return (_content[type]);
//}
//
//unsigned Directory::getFilesNumber(void) const {
//	unsigned long size = 0;
//	for (unsigned long x = 0; x < TYPE_N; x++)
//		size += _content[x].size();
//	return (size);
//}
//
//
//
//const char* _labels[TYPE_N] = {
//	"unknown",
//	"pipe",
//	"character",
//	"directory",
//	"block",
//	"regular file",
//	"symbolic link",
//	"socket",
//	"whiteout"
//};
//
//void Directory::print(const Typeindex type) const {
//	auto ite = _content[type].begin();
//	while (ite != _content[type].end()) {
//		std::cout << _labels[type] << " - " << ite->getName() << std::endl;
//		ite++;
//	}
//}
//
//const char* Directory::getNextFilePath(void) const {
//	/*
//	static auto iterator = _content.begin();
//	if (iterator != _content.end())
//		return ((iterator++)->_name.c_str());
//	iterator = _content.begin();
//	*/
//	return (nullptr);
//}
//
//
//
//void tt() {
//	Typentity types[TYPE_N];
//	for (unsigned long x = 0; x < TYPE_N; x++) {
//		types[x]._label = _labels[x];
//		types[x]._size = sizeof(_labels[x]);
//		types[x]._index = static_cast<Typeindex>(x);
//	}
//
//	static Typentity* _converter[DT_WHT + 1] {
//		&types[T_UNK], &types[T_FIF], &types[T_CHR],
//		nullptr, &types[T_DIR], nullptr,
//		&types[T_BLK], nullptr, &types[T_REG],
//		nullptr, &types[T_LNK], nullptr,
//		&types[T_SOC], nullptr, &types[T_WHT]
//	};
//}
//
//Typeindex Directory::getTypentity(const int type) {
//	switch (type) {
//		case DT_REG:		return (T_REG);
//		case DT_DIR:		return (T_DIR);
//		case DT_LNK:		return (T_LNK);
//		case DT_CHR:		return (T_CHR);
//		case DT_BLK:		return (T_BLK);
//		case DT_WHT:		return (T_WHT);
//		case DT_SOCK:		return (T_UNK);
//		case DT_FIFO:		return (T_FIF);
//		default:			return (T_UNK);
//	} return (T_UNK);
//}
//
//
//// DirEntity default constructor
//DirEntity::DirEntity(void)
//: _name{}, _path{}, _dirent{}, _stat{} {
//	// structures manual initialization
//	std::memset(&_dirent,	0, sizeof(Dirent));
//	std::memset(&_stat,		0, sizeof(Stat));
//}
//
//DirEntity::DirEntity(const String& path, const Dirent* dirent)
//// initialize name and full path
//: _name{dirent->d_name, strlen(dirent->d_name)}, _path{path + _name}, _dirent{}, _stat{}  {
//	// memory copy 'Dirent' structure
//	std::memcpy(&_dirent, dirent, sizeof(Dirent));
//	// get stat data about entity
//	stat(_path.c_str(), &_stat);
//}
//
//DirEntity::~DirEntity(void) {
//	// DirEntity destructor
//}
//
//const String& DirEntity::getName(void) const {
//	return (_name);
//}
//
//const String& DirEntity::getPath(void) const {
//	return (_path);
//}
//
//
//// unix NAME_MAX
//// bsd MAXNAMLEN
//// stdio macro FILENAME_MAX
//
//String DirEntity::getLinkPath(const String& link) {
//	char buff[MAXNAMLEN];
//	int size = readlink(link.c_str(), buff, MAXNAMLEN);
//	if (size == -1)
//		return (perror("symlink"), String());
//	return (String(buff, size));
//}
//
//
//bool DirEntity::makeLink(const String& source, const String& link) {
//	return (symlink(source.c_str(), link.c_str()) == -1 ? ERROR : NOERR);
//}
//
//
//
//
//
//
//
//
//
//
//
