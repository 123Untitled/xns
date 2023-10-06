#include "unit_tests.hpp"
#include "bst_iterator.hpp"

#include "tree.hpp"
#include "time.hpp"
#include "random.hpp"

/* unit test */
template <>
int UT::unit_tests<"bst_iterator">(void) {

	xns::tree<int> tree {};

	for (xns::size_t i = 0; i < 1'000'000; ++i) {
		tree.insert(xns::random::integral<int>());
	}

	constexpr xns::size_t N = 10;

	{
		auto start = xns::time::now();
		// bfs iterator
		for (xns::size_t i = 0; i < N; ++i) {
			auto it = tree.bfs_begin();
			while (it) { ++it; }
		}
		auto end = xns::time::now();
		std::cout << "       bfs iterator -> " << end - start << std::endl;
	}

	{
		auto start = xns::time::now();
		// pre-order iterator
		for (xns::size_t i = 0; i < N; ++i) {
			auto it = tree.pre_order_begin();
			while (it) { ++it; }
		}
		auto end = xns::time::now();
		std::cout << " pre-order iterator -> " << end - start << std::endl;
	}

	{
		auto start = xns::time::now();
		// in-order iterator
		for (xns::size_t i = 0; i < N; ++i) {
			auto it = tree.in_order_begin();
			while (it) { ++it; }
		}
		auto end = xns::time::now();
		std::cout << "  in-order iterator -> " << end - start << std::endl;
	}

	{
		auto start = xns::time::now();
		// post-order iterator
		for (xns::size_t i = 0; i < N; ++i) {
			auto it = tree.post_order_begin();
			while (it) { ++it; }
		}
		auto end = xns::time::now();
		std::cout << "post-order iterator -> " << end - start << std::endl;
	}




	return 0;
}

#if defined(XNS_TEST_BST_ITERATOR)
int main(void) {
	return UT::unit_tests<"bst_iterator">();
}
#endif

