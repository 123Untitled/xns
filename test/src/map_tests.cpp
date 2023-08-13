#include "unit_tests.hpp"
#include "map.hpp"

#include "variant.hpp"

template <>
bool UT::unit_tests<"map">(void) {

	xns::string s1{"hello"};
	xns::string s2{"world"};
	xns::string s3{"this"};
	xns::string s4{"is"};
	xns::string s5{"cool"};

	xns::string_view s6{"a"};
	xns::string_view s7{"b"};

		std::cout << (s6 < s7) << std::endl;
		std::cout << (s6 > s7) << std::endl;



	xns::map<xns::string_view, float> _map;

	_map.insert("hello", 1.0f);
	_map.insert("world", 2.0f);
	_map.insert("this", 3.0f);
	_map.insert("is", 4.0f);
	_map.insert("cool", 5.0f);
	_map.insert("i'm", 6.0f);
	_map.insert("a", 7.0f);
	_map.insert("map", 8.0f);
	_map.insert("with", 9.0f);
	_map.insert("string", 10.0f);
	_map.insert("views", 11.0f);
	_map.insert("as", 12.0f);
	_map.insert("keys", 13.0f);
	_map.insert("and", 14.0f);
	_map.insert("floats", 15.0f);
	_map.insert("as", 16.0f);
	_map.insert("values", 17.0f);





	_map.print();

	//_map.print();

	//int iii = xns::string{"hello"} <= xns::string{"world"};

	//std::cout << iii << std::endl;



	return true;

}

int main(void) {

	UT::unit_tests<"map">();

	return 0;
}
