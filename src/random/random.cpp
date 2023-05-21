#include "random.hpp"

/* singleton instance */
xns::random xns::random::_instance = xns::random{};

/* default constructor */
xns::random::random(void) {
	// seed initialization
	std::srand(std::time(NULL) / getpid());
}

/* destructor */
xns::random::~random(void) {
	// code here...
}

/* random integer */
xns::random::size_type xns::random::random_gen(const size_type range) {
	// return random integer
	return !range ? 0 : std::rand() % range;
}
