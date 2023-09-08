#include "unit_tests.hpp"
#include "trie.hpp"
#include "reference.hpp"

	// -- I S  I N V O C A B L E ----------------------------------------------

	/* is invocable */
	template <typename F, typename... A>
	concept is_invocable = requires(F f, A&&... a) {
		{ f(xns::forward<A>(a)...) };
	};

int func(float) {
	return 0;
}


/* unit test */
template <>
bool UT::unit_tests<"trie">(void) {

	using f = int(float);

	std::cout << "is_invocable<int>(func): " << is_invocable<f> << std::endl;


	int a = 0;
	int b = 99;

	xns::mut_ref<int> ref{a};

	a = 123;

	const int& r = ref;

	xns::const_ref<int> ref2{ref};


	std::cout << r << std::endl;

	a = 23;

	std::cout << r << std::endl;


	return false;
}



int main(void) {
	return UT::unit_tests<"trie">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}
