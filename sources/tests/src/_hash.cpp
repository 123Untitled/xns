#include "unit_tests.hpp"
#include "other/hash.hpp"

#include "containers/pair.hpp"
#include "string/string.hpp"
#include "containers/array.hpp"

/* unit test */

auto unit_tests_hash(void) -> int {

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


	return 0;
}

#if defined(XNS_TEST_HASH)
int main(void) {
	return unit_tests_hash();
}
#endif

