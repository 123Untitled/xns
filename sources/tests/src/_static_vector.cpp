#include "unit_tests.hpp"
#include "static_vector.hpp"

class test final {
public:
	test(void) {
		std::cout << "default constructor" << std::endl;
	}
	test(const test&) {
		std::cout << "copy constructor" << std::endl;
	}
	test(float, int) {
		std::cout << "float, int constructor" << std::endl;
	}
	test(test&&) noexcept(false) {
		std::cout << "move constructor" << std::endl;
	}
	test& operator=(const test&) {
		std::cout << "copy assignment operator" << std::endl;
		return *this;
	}
	test& operator=(test&&) {
		std::cout << "move assignment operator" << std::endl;
		return *this;
	}
	~test(void) {
		std::cout << "destructor" << std::endl;
	}
};



/* unit test */
auto unit_tests_static_vector(void) -> int {

	xns::static_vector<test, 10> v;

	test t;

	v.push_back(t);
	v.push_back(test{});
	v.emplace_back(1.0f, 2);

	v.pop_back();
	std::cout << "size: " << v.size() << std::endl;

	xns::static_vector<test, 10> v2{xns::move(v)};

	std::cout << "size: " << v.size() << std::endl;


	return 0;
}

#if defined(XNS_TEST_STATIC_VECTOR)
int main(void) {
	return unit_tests_static_vector();
}
#endif

