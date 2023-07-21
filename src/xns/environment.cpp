#include "environment.hpp"


// -- E N V I R O N M E N T ---------------------------------------------------


// -- private static members --------------------------------------------------

/* environment variables */
xns::env::vector_type xns::env::_env{};


// -- public static methods ---------------------------------------------------

/* initialize environment */
void xns::env::init(const char** envp) {

	// check pointer validity
	if (envp == nullptr || _env.empty() == false) { return; }

	// loop through environment variables
	for (size_type x = 0; envp[x] != nullptr; ++x) {
		// count until '='
		size_type y = 0;
		while (envp[x][y] && envp[x][y] != '=') { ++y; }
		// add key-value pair
		_env.emplace_back(
			xns::string{envp[x], y},
			xns::string{envp[x] + y + 1}
		);
	}
}

/* print environment */
void xns::env::print(void) {
	// loop over environment variables
	for (size_type x = 0; x < _env.size(); ++x) {
		// print variable
		xns::output::write(_env[x]._first);
		xns::output::write(" [=] ", 5);
		xns::output::write(_env[x]._second);
		xns::output::write("\n", 1);
	} // flush output
	xns::output::render();
}


// -- public methods ----------------------------------------------------------

/* get environment variable */
const xns::env::weak_string xns::env::get(const xns::string& name) {

	// loop over environment variables
	for (size_type x = 0; x < _env.size(); ++x) {
		// check if key matches
		if (_env[x]._first == name) {
			// return value
			return weak_string{&_env[x]._second}; }
	} // else return nullptr
	return nullptr;
}



