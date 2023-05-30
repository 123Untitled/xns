#include "unit_tests.hpp"

#include <filesystem>

// this is a unit test to compare simplified path resolution with std::filesystem

bool UT::path_ut(void) {

	using path_t = xns::path<xns::string_view>;
	path_t p1;
	{
	// original path
	const char* str = "../../xns/../../../../lib/log.txt/.";
	//const wchar_t* wstr = L"../../xns/../../../../lib/log.txt/.";
	xns::cstring str2 = str;

	std::cout << "original path: " << str << std::endl;

	xns::string_view sv = str2.pointer();
	// simplified path


		p1 = sv;
	}


	// print simplified path
	std::cout << "simplified path: " << std::flush;
	for (path_t::size_type x = 0; x < p1.count(); ++x) {
		write(1, p1.string(x).data(), p1.string(x).size());
		//std::cout << p1[x].get<0>().data();
		if (x < p1.count() - 1) {
			std::cout << "/"<< std::flush; }
	} std::cout << std::endl;


	return true;
}