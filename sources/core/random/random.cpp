#include "random/random.hpp"

/* singleton instance */
xns::random xns::random::_instance = xns::random{};

/* default constructor */
xns::random::random(void) {
	unsigned int time = static_cast<unsigned int>(std::time(NULL));
	unsigned int pid = static_cast<unsigned int>(getpid());
	// seed initialization
	std::srand(time / pid);
}

/* destructor */
xns::random::~random(void) {
	// code here...
}

/* random integer */
xns::random::size_type xns::random::random_gen(const size_type range) {
	// return random integer
	return !range ? 0 : static_cast<size_type>(std::rand()) % range;
}

/* random boolean */
bool xns::random::random_bool(void) {
	// return random boolean
	return std::rand() % 2;
}
