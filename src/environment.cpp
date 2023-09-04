#include "environment.hpp"

// environ
extern constinit const char** environ;


// -- E N V I R O N M E N T ---------------------------------------------------


// -- private lifecycle -------------------------------------------------------

/* default constructor */
xns::env::env(void)
: _env{} {
	// initialize environment
	init(environ);
}


// -- private modifiers -------------------------------------------------------

/* initialize environment */
auto xns::env::init(const char** envp) -> void {

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

	auto& instance = xns::env::shared();

	// loop over environment variables
	for (size_type x = 0; x < instance._env.size(); ++x) {
		// print variable
		xns::out::write(xns::get<0>(instance._env[x]));
		xns::out::write(" [=] ", 5);
		xns::out::write(xns::get<1>(instance._env[x]));
		xns::out::write("\n", 1);
	} // flush output
	xns::out::render();
}


// -- public methods ----------------------------------------------------------

/* get environment variable */
auto xns::env::get(const xns::string& name) noexcept -> const xns::env::weak_string {

	auto& instance = xns::env::shared();

	// loop over environment variables
	for (size_type x = 0; x < instance._env.size(); ++x) {
		// check if key matches
		if (xns::get<0>(instance._env[x]) == name) {
			// return value
			return weak_string{&xns::get<1>(instance._env[x])}; }
	} // else return nullptr
	return nullptr;
}

/* get paths */
auto xns::env::paths(void) -> xns::vector<xns::string> {

	weak_string weak{get("PATH")};

	if (weak == nullptr) { return{}; }

	return weak->split(":");
}



