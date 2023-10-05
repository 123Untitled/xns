#include "access.hpp"


// -- A C C E S S -------------------------------------------------------------


// -- public static methods ---------------------------------------------------

/* check execution access */
bool xns::access::x_ok(const xns::string& path) noexcept {
	return ::access(path.data(), X_OK) == 0;
}

/* check read access */
bool xns::access::r_ok(const xns::string& path) noexcept {
	return ::access(path.data(), R_OK) == 0;
}

/* check write access */
bool xns::access::w_ok(const xns::string& path) noexcept {
	return ::access(path.data(), W_OK) == 0;
}

/* check existence */
bool xns::access::f_ok(const xns::string& path) noexcept {
	return ::access(path.data(), F_OK) == 0;
}


/* get execution access */
bool xns::access::sys_x_ok(xns::string& exec) {

	auto paths{xns::env::paths()};

	xns::string buffer{};

	for (xns::size_t x = 0; x < paths.size(); ++x) {

		buffer.reserve(paths[x].size()
					   + 1
					   + exec.size());

		buffer.append(paths[x]);
		buffer.append('/');
		buffer.append(exec);

		if (::access(buffer.data(), X_OK) == 0) {
			exec = xns::move(buffer);
			return true;
		}

		buffer.clear();


	}
	return false;
}


// -- public constructors -----------------------------------------------------

/* default constructor */
xns::access::access(void) noexcept
//:
{
	// code here...
}

/* copy constructor */
xns::access::access(const access& other) noexcept
//:
{
	// code here...
}

/* move constructor */
xns::access::access(access&& other) noexcept
//:
{
	// code here...
}

/* destructor */
xns::access::~access(void) noexcept {
	// code here...
}


// -- public assignment operators ---------------------------------------------

/* copy assignment operator */
xns::access& xns::access::operator=(const access& other) noexcept {
	// check for self assignment
	if (this != &other) {
	} // return self reference
	return *this;
}

/* move assignment operator */
xns::access& xns::access::operator=(access&& other) noexcept {
	// check for self assignment
	if (this != &other) {
	} // return self reference
	return *this;
}
