#include "random.hpp"


/* singleton instance */
Xf::Random Xf::Random::_instance;

/* default constructor */
Xf::Random::Random(void) {
	// seed initialization
	std::srand(std::time(NULL) / getpid());
}

/* destructor */
Xf::Random::~Random(void) {
	// code here...
}

/* random integer */
Xf::Random::Size Xf::Random::random(const Size range) {
	// get instance
	Random& instance = _instance;

	return !range ? 0 : std::rand() % range;
}
