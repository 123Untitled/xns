#include "unit_tests.hpp"
#include "reference.hpp"

#include <vector>

template <>
bool UT::unit_tests<"reference">(void) {

	int i = 5;
	int j = 6;
	int k = 7;
	int l = 8;
	xns::reference ref{i};

	//xns::reference refref{ref};
	xns::reference<xns::reference<int>> refref{ref};

	int& iref = ref;


	std::vector<xns::reference<int>> vec{{ref, j, k, l}};
	vec.push_back(i);

	return true;

}
