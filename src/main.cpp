#include "xns.hpp"

#include <array>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <stack>
#include <any>





template <class T>
struct type_name {

		static constexpr const char* name(void) {

			if constexpr (xns::is_same<T, int>) {
				return "int";
			}
			if constexpr (xns::is_same<T, float>) {
				return "float";
			}

				return "unknown";
		}
};

void funcc(void);

class TT {

	public:

		TT(void) {
			std::cout << "TT::TT()" << std::endl;
		}

		~TT(void) {
			std::cout << "TT::~TT()" << std::endl;
		}

		NON_ASSIGNABLE(TT);
};

#include "unit_tests.hpp"


#if !defined(XNS_UT)
int main(int ac, char** av) {


	UT::path_ut();






	return EXIT_SUCCESS;










	Xf::Trie<xns::cstring> trie;

	xns::vector<xns::cstring> v;

	v.emplace_back("cd");
	v.emplace_back("go");
	v.emplace_back("move");

	trie.insert(v, "!!!");

	for (xns::vector<xns::cstring>::size_type x = 0; x < v.size(); ++x) {
		auto weak = trie.find(v[x]);
		if (weak != nullptr) {
			std::cout.write(weak->pointer(), weak->size()) << std::endl;
			std::cout << (xns::size_t)weak->pointer() << std::endl;
		}
		else {
			std::cout << "not found" << std::endl;
		}
	}

	return EXIT_SUCCESS;




}
#endif





