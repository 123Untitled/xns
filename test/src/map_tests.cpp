#include "unit_tests.hpp"
#include "map.hpp"

#include "variant.hpp"
#include "random.hpp"
#include <chrono>
#include <map>
#include <set>



void benchmark(void) {

	// get time in nanoseconds
	auto get_time = []() -> auto {
		return std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	};


	constexpr std::size_t N = 10000000;

	{

		// get time in nanoseconds
		auto start = get_time();

		{
			xns::map<int, float> _map;

			for (xns::size_t i = 0; i < N; ++i) {
				_map.insert(xns::random::integral<int>() % 50, 0.0f);
			}
		}

		// get time in nanoseconds
		auto end = get_time();
		std::cout << "[xns::map] time: " << (end - start) << " ns" << std::endl;

	}

	{
		// get time in nanoseconds
		auto start = get_time();

		{
			std::set<int> _map;

			for (xns::size_t i = 0; i < N; ++i) {
				_map.insert(xns::random::integral<int>() % 50);
			}
		}

		// get time in nanoseconds
		auto end = get_time();
		std::cout << "[std::map] time: " << (end - start) << " ns" << std::endl;
	}




}

template <>
bool UT::unit_tests<"map">(void) {

	benchmark();
	return true;

	xns::map<int, float> _map;
	return true;

	for (xns::size_t i = 0; i < 15; ++i) {
		_map.insert(xns::random::integral<int>() % 50, 0.0f);
	}




	_map.print();

	//_map.print();

	//int iii = xns::string{"hello"} <= xns::string{"world"};

	//std::cout << iii << std::endl;



	return true;

}




int main(void) {


	UT::unit_tests<"map">();

	return 0;
}
