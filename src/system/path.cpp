#include "path.hpp"


/* default constructor */
xns::path::path(void)
: _segments{}, _type{path_type::UNDEFINED} {
	// ...
}

/* path constructor */
xns::path::path(const string& path)
: _segments{}, _type{path_type::UNDEFINED} {
	// resolve path
	resolve(path);
}

/* move constructor */
xns::path::path(path&& other) noexcept
: _segments(xns::move(other._segments)), _type(xns::move(other._type)) {
	// nothing to do
}

/* path assignment */
xns::path& xns::path::assign(const string& path) {
	// resolve path
	resolve(path);
	// return self reference
	return *this;
}


/* move assignment */
xns::path& xns::path::assign(path&& other) noexcept {
	// check for self-assignment
	if (this != &other) {
		// move members
		_segments = xns::move(other._segments);
		_type     = xns::move(other._type);
	} // return self reference
	return *this;
}

/* path assignment operator */
xns::path& xns::path::operator=(const string& path) {
	// return path assignment
	return assign(path);
}

/* move assignment operator */
xns::path& xns::path::operator=(path&& other) noexcept {
	// return move assignment
	return assign(xns::move(other));
}

/* segment accessor */
const xns::path::segment& xns::path::operator[](const size_type index) const {
	// return segment
	return _segments[index];
}

/* segment count */
xns::path::size_type xns::path::count(void) const {
	// return segment count
	return _segments.size();
}

/* resolve path */
void xns::path::resolve(const string& path) {

	// clear previous segments if any
	_segments.clear();
	// allocate space for segments
	_segments.reserve(16);

	// loop over characters in path
	for (string::size_type x = 0, z = 0; x < path.size(); x += z, z = 0) {

		// skip separator
		while (path[x] == SEP) { ++x; }
		// count characters
		while (path[x + z] != EOS && path[x + z] != SEP) { ++z; }
		// check for empty segment
		if (z == 0) { continue; }
		// skip current segment
		if (z == 1 && path[x] == CUR) { continue; }

		// check for parent segment
		if (z == 2 && path[x] == CUR && path[x + 1] == CUR) {
			// check for previous parent segment
			if (_segments.empty()
				|| _segments.back().get<1>() == segment_type::PARENT) {
				// add parent segment
				_segments.emplace_back(string{&path[x], z}, segment_type::PARENT);
			} // else remove previous segment
			else { _segments.pop_back(); }
		}

		// add entity segment
		else {
			_segments.emplace_back(string{&path[x], z}, segment_type::ENTITY);
		}
	}

	// set path type
	if (!path.empty() && path[0] == SEP) {
		// set absolute path type
		_type = path_type::ABSOLUTE;
	} // set relative path type
	else { _type = path_type::RELATIVE; }

}

