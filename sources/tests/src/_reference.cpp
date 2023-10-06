#include "unit_tests.hpp"
#include "reference.hpp"

#include <vector>

template <>
int UT::unit_tests<"reference">(void) {

	int i = 5;
	int j = 6;
	int k = 7;
	int l = 8;
	xns::reference ref{i};

	xns::reference refref{ref};
	xns::reference<xns::reference<int>> refrefref{ref};

	xns::reference<int>& val = refrefref;


	int& iref = ref;


	std::vector<xns::reference<int>> vec{};
	//std::vector<xns::reference<int>> vec{{ref, j, k, l}};
	//vec.push_back(i); // NEED TO FIX THIS

	return 0;

}

#if defined(XNS_TEST_REFERENCE)
int main(void) {
	return UT::unit_tests<"reference">();
}
#endif

