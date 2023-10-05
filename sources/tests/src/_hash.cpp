#include "unit_tests.hpp"
#include "hash.hpp"

#include "pair.hpp"
#include "string.hpp"
#include "array.hpp"

/* unit test */
template <>
bool UT::unit_tests<"hash">(void) {

	using pair = xns::pair<xns::string, xns::u64>;

	xns::array arr{
		pair{ "Hello", 0U },
		pair{ "World", 0U },
		pair{ "my",    0U },
		pair{ "name",  0U },
		pair{ "is",    0U },
		pair{ "John",  0U }
	};

	constexpr xns::size_t DEFAULT_BUCKET_SIZE = 128;

	for (xns::size_t i = 0; i < arr.size(); ++i) {
		xns::get<xns::u64>(arr[i]) = xns::hash(xns::get<xns::string>(arr[i]));
		xns::u64 hash = xns::get<xns::u64>(arr[i]) % DEFAULT_BUCKET_SIZE;
		std::cout << xns::get<xns::string>(arr[i]) << " -> " << hash << std::endl;
	}

	std::cout << "array hash: " << xns::hash(arr) << std::endl;


	return false;
}

int main(void) {



	return UT::unit_tests<"hash">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}
