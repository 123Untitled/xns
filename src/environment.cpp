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
		xns::out::write(xns::get<0>(_env[x]));
		xns::out::write(" [=] ", 5);
		xns::out::write(xns::get<1>(_env[x]));
		xns::out::write("\n", 1);
	} // flush output
	xns::out::flush();
}


// -- public methods ----------------------------------------------------------

/* get environment variable */
const xns::env::weak_string xns::env::get(const xns::string& name) {

	// loop over environment variables
	for (size_type x = 0; x < _env.size(); ++x) {
		// check if key matches
		if (xns::get<0>(_env[x]) == name) {
			// return value
			return weak_string{&xns::get<1>(_env[x])}; }
	} // else return nullptr
	return nullptr;
}

/* get paths */
xns::vector<xns::string> xns::env::paths(void) {

	weak_string weak{get("PATH")};

	if (weak == nullptr) { return{}; }

	return weak->split(":");
}



