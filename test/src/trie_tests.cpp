#include "unit_tests.hpp"
#include "trie.hpp"
#include "reference.hpp"


/* unit test */
template <>
bool UT::unit_tests<"trie">(void) {

	xns::trie<int> tr;


	return false;
}



int main(void) {
	return UT::unit_tests<"trie">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}
