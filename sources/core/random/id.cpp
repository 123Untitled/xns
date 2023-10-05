#include "id.hpp"

xns::string xns::id::generate(void) {

	string id{};

	xns::size_t rnd;

	char_t buffer[4];

	// generate random letter
	rnd = xns::random::random_gen(ALPHA_COMB);
	buffer[0] = _alpha[rnd][0];
	buffer[1] = _alpha[rnd][1];

	// generate random number
	rnd = xns::random::random_gen(DIGIT_COMB);
	buffer[2] = _digit[rnd][0];
	buffer[3] = _digit[rnd][1];

	id.assign(buffer, 4);

	return id;
}
