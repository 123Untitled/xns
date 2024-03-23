#include "xns/containers/vector.hpp"
#include "xns/random/random.hpp"
#include "xns/time/time.hpp"


// -- types -------------------------------------------------------------------

template <typename __type>
using __vec = xns::vector<__type>;


/* is equal */
template <typename __type, bool __capacity = true>
static auto is_equal(const __vec<__type>& __v1,
					 const __vec<__type>& __v2) noexcept -> bool {

	if (__v1.size() != __v2.size())
		return false;

	if constexpr (__capacity == true) {
		if (__v1.capacity() != __v2.capacity())
			return false; }

	for (auto i = 0; i < __v1.size(); ++i)
		if (__v1[i] != __v2[i])
			return false;

	return true;
}


// -- constructors ------------------------------------------------------------

static auto constructors_test(void) -> void {
}


static void dichotomic_test(void) {
	xns::vector<int> v = xns::make_vector<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

	// initialize seed
	std::srand((unsigned)std::time(nullptr));

	xns::vector<int> vvv{};
	for (int i = 0; i < 100; ++i) {
		//vvv.copy_back(std::rand() % 1000);
		vvv.dichotomic_insert(std::rand() % 100000);
	}

	for (auto& i : vvv) {
		std::cout << i << ", ";
	}
	std::cout << std::endl;


	auto it = vvv.dichotomic_search(1000);

	if (it != vvv.end()) {
		std::cout << "found: " << *it << std::endl;
	} else {
		std::cout << "not found" << std::endl;
	}
}

static auto simd_test(void) -> void {

	using size_type = typename xns::vector<int>::size_type;

	xns::vector<int> vec;

	constexpr size_type N = 1'000'000;

	for (size_type i = 0; i < N; ++i) {
		vec.push_back(xns::random::integral<int>());
	}

	auto start = xns::time::now();

	for (size_type i = 0; i < 100; ++i) {
		xns::vector<int> vc{vec};
	}

	auto end = xns::time::now();

	std::cout << "copy: " << end - start << " ns" << std::endl;

}

class A {
public:
	A(void) = default;
	A(const A&) = default;
	A(A&&) noexcept(false) = default;
	A& operator=(const A&) = default;
	A& operator=(A&&) = default;
	~A(void) = default;
};


/* unit test */
auto unit_tests_vector(void) -> int {

	simd_test();

	xns::vector<A> v;


	return 0;
}



#if defined(XNS_TEST_VECTOR)
int main(void) {
	return unit_tests_vector();
}
#endif
