#include "unit_tests.hpp"
#include "variant.hpp"
#include "string.hpp"

#include "reference.hpp"
#include "testclass.hpp"

#include "random.hpp"
#include "benchmark.hpp"

#include <string>
#include <vector>
#include <chrono>


static size_t check_sum = 0;

void benchmark(void) {

	using xvariant = xns::variant<std::vector<xns::size_t>, std::string, int>;
	using svariant = std::variant<std::vector<xns::size_t>, std::string, int>;


	constexpr xns::size_t N = 10000;
	xns::benchmark<5> bench;


	bench.run("xns::variant", []() {


		for (xns::size_t i = 0; i < N; ++i) {
			xvariant var{xns::in_place_type<int>{}, xns::random::integral<int>()};

			var.emplace<std::vector<xns::size_t>>(std::initializer_list<xns::size_t>{1, 2, 3, 4, 5, 6, 7, 8, 9});
			if (var.has<std::vector<xns::size_t>>()) {
				check_sum ^= (xns::size_t)xns::get<std::vector<xns::size_t>>(var)[xns::random::integral<xns::size_t>() % 9];
			}
			var.emplace<std::string>("hello world");
			if (var.has<std::string>()) {
				check_sum ^= (xns::size_t)xns::get<std::string>(var)[xns::random::integral<xns::size_t>() % 11];
			}
		}
	});

	bench.run("std::variant", []() {


		for (xns::size_t i = 0; i < N; ++i) {
			svariant var{std::in_place_type<int>, xns::random::integral<int>()};

			var.emplace<std::vector<xns::size_t>>(std::initializer_list<xns::size_t>{1, 2, 3, 4, 5, 6, 7, 8, 9});
			if (std::holds_alternative<std::vector<xns::size_t>>(var)) {
				check_sum ^= (xns::size_t)std::get<std::vector<xns::size_t>>(var)[xns::random::integral<xns::size_t>() % 9];
			}
			var.emplace<std::string>("hello world");
			if (std::holds_alternative<std::string>(var)) {
				check_sum ^= (xns::size_t)std::get<std::string>(var)[xns::random::integral<xns::size_t>() % 11];
			}
		}
	});


	bench.result("variant");

	std::cout << "check_sum: " << check_sum << std::endl;


}


/* unit test */
template <>
int UT::unit_tests<"variant">(void) {


	xns::variant<C, B, D> v0{};

	v0.emplace<C>('c');


	auto c = xns::get<B>(xns::move(v0));

	benchmark();



	return 0;
}


#if defined(XNS_TEST_VARIANT)
int main(void) {
	return UT::unit_tests<"variant">();
}
#endif

