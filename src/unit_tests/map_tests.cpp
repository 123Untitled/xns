#include "unit_tests.hpp"
#include "map.hpp"


template <>
bool UT::unit_tests<"map">(void) {

	xns::map<xns::string, float> _map;

	_map.insert("hello", 1.0f);
	_map.insert("world", 2.0f);
	_map.insert("this", 3.0f);
	_map.insert("is", 4.0f);
	_map.insert("cool", 5.0f);

	_map.print();

	//_map.print();

	int iii = xns::string{"hello"} <= xns::string{"world"};

	std::cout << iii << std::endl;



	return true;

}

