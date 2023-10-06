#include "unit_tests.hpp"
#include "queue.hpp"
#include "tree.hpp"
#include "random.hpp"
#include "time.hpp"

/* unit test */
template <>
int UT::unit_tests<"queue">(void) {

	// old allocator
	// bfs 1000000  nodes:  20545625 ns
	// bfs 10000000 nodes: 242689709 ns

	// pool allocator
	// bfs 1000000  nodes:  22975208 ns
	// bfs 10000000 nodes: 277427833 ns

	// new
	// bfs 1000000  nodes:  47611542 ns
	// bfs 10000000 nodes: 578603791 ns




	xns::tree<int> tree;

	constexpr xns::size_t N = 1000;

	for (xns::size_t i = 0; i < N; ++i)
		tree.insert(xns::random::integral<int>());


	auto start = xns::time::now();
	auto it = tree.bfs_begin();


	while (it) { ++it; }


	auto end = xns::time::now();

	std::cout << "bfs " << N << " nodes: " << end - start << " ns\n";



	// code here...
	return 0;
}

#if defined(XNS_TEST_QUEUE)
int main(void) {
	return UT::unit_tests<"queue">();
}
#endif

