#include "unit_tests.hpp"
#include "variant.hpp"
#include "string.hpp"

#include "reference_wrapper.hpp"

#include "random.hpp"
#include "benchmark.hpp"

#include <string>
#include <vector>
#include <chrono>
#include <variant>


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

	return;

	bench.result("variant");

	std::cout << "check_sum: " << check_sum << std::endl;


}


template <typename T1, typename T2>
auto sizeof_test_impl(void) -> int {
	std::cout << "                 T1: " << sizeof(T1) << std::endl;
	std::cout << "                 T2: " << sizeof(T2) << std::endl;
	std::cout << "sizeof xns::variant: " << sizeof(xns::variant<T1, T2>) << std::endl;
	std::cout << "sizeof std::variant: " << sizeof(std::variant<T1, T2>) << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	return sizeof(xns::variant<T1, T2>) != sizeof(std::variant<T1, T2>);
}

template <typename T1, typename T2, typename... Ts> requires (sizeof...(Ts) > 0
														   && sizeof...(Ts) % 2 == 0)
auto sizeof_test_impl(void) -> int {
	return sizeof_test_impl<T1, T2>() + sizeof_test_impl<Ts...>();
}

template <typename... T>
auto sizeof_test(void) -> int {
	std::cout << "----------------------------------------" << std::endl;
	return sizeof_test_impl<T...>();
}


/* unit test */

auto unit_tests_variant(void) -> int {


	sizeof_test<int, int,
				char, float,
				double, char,
				int, short,
				std::string, std::vector<int>,
				std::string, char,
				double, float>();



	//using T1 = double;
	//using T2 = char;
	//
	//std::cout << "T1: " << sizeof(T1) << std::endl;
	//std::cout << "T2: " << sizeof(T2) << std::endl;
	//
	//std::cout << "sizeof xns::variant: " << sizeof(xns::variant<T1, T2>) << std::endl;
	//std::cout << "sizeof std::variant: " << sizeof(std::variant<T1, T2>) << std::endl;
	return 0;

	/*
	std::variant<const int, float> v0{1};

	v0.emplace<float>(1.0f);
	std::get<float>(v0) = 2.0f;
	v0.emplace<const int>(2);
	//std::get<const int>(v0) = 3;


	xns::variant<const int, float> v1{xns::in_place_type<const int>{}, 1};
	v1.emplace<float>(1.0f);
	xns::get<float>(v1) = 2.0f;
	v1.emplace<const int>(2);
	//xns::get<const int>(v1) = 3;

	xns::variant<int, int> v;
	xns::get<int>(v) = 1;
	*/



	//xns::variant<C, B, D> v0{};
	//
	//v0.emplace<C>('c');

	//auto c = xns::get<B>(xns::move(v0));

	benchmark();



	return 0;
}


#if defined(XNS_TEST_VARIANT)
int main(void) {
	return unit_tests_variant();
}
#endif

