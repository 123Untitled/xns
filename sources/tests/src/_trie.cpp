#include "unit_tests.hpp"
#include "trie.hpp"
#include "reference_wrapper.hpp"


/* unit test */

auto unit_tests_trie(void) -> int {

	xns::trie<int> tr;


	return 0;
}

#if defined(XNS_TEST_TRIE)
int main(void) {
	return unit_tests_trie();
}
#endif

