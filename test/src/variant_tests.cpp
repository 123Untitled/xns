#include "unit_tests.hpp"
#include "variant.hpp"
#include "string.hpp"

#include "reference.hpp"
#include "testclass.hpp"

#include <string>
#include <vector>
#include <chrono>


template <typename T>
void benchmark(void) {

	using variant = T;

	// get time in nanoseconds
	auto get_time = []() -> auto {
		return std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	};

	// get time in nanoseconds
	auto start = get_time();

	constexpr std::size_t N = 1000000;

	std::vector<variant> vec;

	for (std::size_t i = 0; i < N; ++i) {
		vec.push_back(variant{});
	}

	for (std::size_t i = 0; i < N; ++i) {
		variant& var = vec[i];
		var.template emplace<std::size_t>(i);
	}

	for (std::size_t i = 0; i < N; ++i) {
		variant& var = vec[i];
		var.template emplace<float>(123.456f);
	}

	for (std::size_t i = 0; i < N; ++i) {
		variant& var = vec[i];
		var.template emplace<std::string>("hello world");
	}


	std::vector<variant> vec2;

	for (std::size_t i = 0; i < N; ++i) {
		vec2.push_back(vec[i]);
	}

	std::vector<variant> vec3;

	for (std::size_t i = 0; i < N; ++i) {
		vec3.push_back(std::move(vec[i]));
	}

	// get time in nanoseconds
	auto end = get_time();

	long long ms = (end - start);
	// / 1000000.0);

	// print time in milliseconds
	std::cout << "time: " << ms << " ns" << std::endl;

}


/* unit test */
template <>
bool UT::unit_tests<"variant">(void) {


	xns::variant<C, B, D> v0{};

	v0.emplace<C>('c');


	auto c = xns::get<3>(xns::move(v0));




	return true;
}



int main(void) {

	//benchmark<xns::variant<std::string, std::size_t, float>>();
	//benchmark<std::variant<std::string, std::size_t, float>>();



	return UT::unit_tests<"variant">()
		? EXIT_SUCCESS : EXIT_FAILURE;
};
