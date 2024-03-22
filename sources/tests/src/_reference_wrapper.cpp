#include "unit_tests.hpp"
#include "containers/reference_wrapper.hpp"

#include <vector>

class A final {
	public:
		void print(const char* str) {
			std::cout << str << std::endl;
		}
};

void print(const char* str) {
	std::cout << str << std::endl;
}

auto unit_tests_reference_wrapper(void) -> int {


	{
		A a;

		auto ref = xns::ref(a);

		xns::invoke(&A::print, ref, "Hello World!");

	}



	int i = 5;
	int j = 6;
	int k = 7;
	int l = 8;
	xns::reference_wrapper ref{i};

	xns::reference_wrapper refref{ref};
	xns::reference_wrapper<xns::reference_wrapper<int>> refrefref{ref};

	xns::reference_wrapper<int>& val = refrefref;


	int& iref = ref;


	std::vector<xns::reference_wrapper<int>> vec{};
	//std::vector<xns::reference<int>> vec{{ref, j, k, l}};
	//vec.push_back(i); // NEED TO FIX THIS

	return 0;

}

#if defined(XNS_TEST_REFERENCE_WRAPPER)
int main(void) {
	return unit_tests_reference_wrapper();
}
#endif

