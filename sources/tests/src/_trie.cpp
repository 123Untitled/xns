#include "unit_tests.hpp"
#include "trie.hpp"
#include "reference.hpp"


/* unit test */
template <>
int UT::unit_tests<"trie">(void) {

	xns::trie<int> tr;


	return 0;
}

#if defined(XNS_TEST_TRIE)
int main(void) {
	return UT::unit_tests<"trie">();
}
#endif

