#include "unit_tests.hpp"
#include "memory.hpp"
#include "allocator.hpp"

#include "tuple.hpp"
#include "time.hpp"

template <xns::size_t N, typename T>
class test {
	T c[N];
};

/* unit test */
template <>
int UT::unit_tests<"memory">(void) {

	constexpr xns::size_t N = 100000000;

	xns::memory::pool<xns::size_t>::init();

	std::vector<xns::size_t*> v;

	v.reserve(N);


	{
		auto start = xns::time::now();

		for (xns::size_t i = 0; i < N; ++i) {
			v.push_back(xns::memory::pool<xns::size_t>::make(i));
		}
		for (xns::size_t i = 0; i < N; ++i) {
			xns::memory::pool<xns::size_t>::store(v[i]);
		}

		auto end = xns::time::now();

		std::cout << "linear allocator: " << std::right << std::setw(15) << end - start << " ns\n";
	}
	v.clear();

	{
		auto start = xns::time::now();

		for (xns::size_t i = 0; i < N; ++i) {
			v.push_back(new xns::size_t{i});
		}

		for (xns::size_t i = 0; i < N; ++i) {
			delete v[i];
		}

		auto end = xns::time::now();

		std::cout << "      new/delete: " << std::right << std::setw(15) << end - start << " ns\n";
	}

	return 0;
}

#if defined(XNS_TEST_MEMORY)
int main(void) {
	return UT::unit_tests<"memory">();
}
#endif

