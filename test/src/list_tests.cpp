#include "unit_tests.hpp"
#include "list.hpp"

#include <unistd.h>
#include <vector>

/* unit test */
template <>
bool UT::unit_tests<"list">(void) {

	xns::list<const int> list;

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_front(0);
	list.push_front(-1);
	list.push_front(-2);


	for (const auto& ref : list) {

		const int& ref2 = ref;

		std::cout << ref2 << std::endl;
	}

	return false;



	return false;


	xns::list<const int>::iterator it = list.begin();

	while (it != list.end()) {
		std::cout << *it << std::endl;
		++it;
	}

	xns::list<const int>::const_iterator cit = list.begin();

	while (cit != list.end()) {
		const int& ref = *cit;

		std::cout << *cit << std::endl;
		++cit;
	}


	const int a = 1;
	int b = 2;
	int* cp = &b;
	const int* cpc = &b;
	const int& ar = a;

	xns::list<int> list2 = xns::make_list(a, b, *cp, *cpc, ar);

	xns::list<int>::iterator it2 = list2.begin();

	::write(1, "\n", 1);
	::write(1, "\n", 1);

	while (it2 != list2.end()) {
		std::cout << *it2 << std::endl;
		++it2;
	}
	::write(1, "\n", 1);
	::write(1, "\n", 1);

	// expected print:
	std::cout << "1" << std::endl;
	std::cout << "2" << std::endl;
	std::cout << "2" << std::endl;
	std::cout << "2" << std::endl;
	std::cout << "1" << std::endl;





	return false;

	std::cout << list.front() << std::endl;
	std::cout << list.back() << std::endl;

	list.pop_back();

	std::cout << list.back() << std::endl;



	// code here...
	return false;
}

