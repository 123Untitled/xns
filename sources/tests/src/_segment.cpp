#include "unit_tests.hpp"
#include "segment.hpp"
#include "random.hpp"
#include "benchmark.hpp"
#include "list.hpp"
#include "vector.hpp"
#include "tree.hpp"
#include "stack.hpp"
#include "queue.hpp"

#include <vector>
#include <queue>
#include <stack>
#include <list>

static xns::size_t NSIZE = 1'000'000;
static xns::size_t sum_check = 0;

static auto benchmark(void) -> void {

	using type = xns::size_t;


	xns::benchmark<1> bench{};

	for (int i = 0; i < 6; ++i) {


		 bench.run("std::list push_back", []() -> void {
			std::list<type> list;
			for (xns::size_t i = 0; i < NSIZE; ++i) {
				list.push_back(xns::random::integral<type>());
				sum_check ^= list.back();
			}
		});

		bench.run("xns::list push_back", []() -> void {
			xns::list<type> xlist;
			for (xns::size_t i = 0; i < NSIZE; ++i) {
				xlist.push_back(xns::random::integral<type>());
				sum_check ^= xlist.back();
			}
		});

		/*
		bench.run("std::vector push_back", []() -> void {
				std::vector<type> vec;
				for (xns::size_t i = 0; i < NSIZE; ++i) {
					vec.push_back(xns::random::integral<type>());
					sum_check ^= vec.back();
				}
		});
		*/

		/*
		bench.run("xns::vector push_back", []() -> void {
				xns::vector<type> vec;
				for (xns::size_t i = 0; i < NSIZE; ++i) {
					vec.push_back(xns::random::integral<type>());
					sum_check ^= vec.back();
				}
		}); */


		bench.run("xns::segment push_back", []() -> void {
				xns::segment<type> seg;
				for (xns::size_t i = 0; i < NSIZE; ++i) {
					seg.push_back(xns::random::integral<type>());
					// sum_check ^= seg[0];
				}
		});


		/*
		bench.run("xns::stack push_back", []() -> void {
				xns::stack<type> tree;
				for (xns::size_t i = 0; i < NSIZE; ++i) {
					tree.push(xns::random::integral<type>());
					sum_check ^= tree.top();
				}
		});*/

		/* bench.run("std::stack push_back", []() -> void {
				std::stack<type> tree;
				for (xns::size_t i = 0; i < NSIZE; ++i) {
					tree.push(xns::random::integral<type>());
					sum_check ^= tree.top();
				}
		}); */

		/*
		bench.run("xns::queue push_back", []() -> void {
				xns::queue<type> tree;
				for (xns::size_t i = 0; i < NSIZE; ++i) {
					tree.enqueue(xns::random::integral<type>());
					sum_check ^= tree.next();
				}
		});*/

		/* bench.run("std::queue push_back", []() -> void {
				std::queue<type> tree;
				for (xns::size_t i = 0; i < NSIZE; ++i) {
					tree.push(xns::random::integral<type>());
					sum_check ^= tree.front();
				}
		}); */


		bench.result("push_back");

	}




	std::cout << "sum_check: " << sum_check << std::endl;



}

/* unit test */
template <>
int UT::unit_tests<"segment">(void) {

	xns::segment<int> seg;

	for (xns::size_t i = 0; i < 50; ++i) {
		seg.push_back(i);
	}

	seg.print();


	for (xns::size_t i = 0; i < seg.size(); ++i) {
		std::cout << seg[i] << " ";
	}
	std::cout << std::endl;

	seg.flatten();

	seg.print();


	benchmark();
	// code here...
	return 0;
}

#if defined(XNS_TEST_SEGMENT)
int main(void) {
	return UT::unit_tests<"segment">();
}
#endif


