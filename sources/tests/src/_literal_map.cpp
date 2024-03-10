#include "unit_tests.hpp"
#include "literal_map.hpp"



auto unit_tests_literal_map(void) -> int {


	//xns::literal_map<int, "a", "b"> m1 = { 1, 2 };
	//
	//m1.have_key<"a">();
	//
	//std::cout << xns::get<"a">(m1) << std::endl;
	//
	//xns::get<"a">(m1) = xns::move(xns::get<"b">(m1));
	//
	//std::cout << xns::get<"a">(m1) << std::endl;


	return 0;


	//constexpr xns::literal_map<int, "hello", "world", "this", "is", "cool"> instance = { 1, 2, 3, 4, 5 };
	//
	//
	//instance.for_each([](const int& v) {
	//	std::cout << v << " ";
	//});
	//std::cout << std::endl;
	//
	//auto m2{instance};
	//
	//m2.for_each([](const int& v) {
	//	std::cout << v << " ";
	//});
	//std::cout << std::endl;
	//
	//std::cout << m2.contains(10) << std::endl;
	//
	//
	//
	//constexpr xns::basic_string_literal sf{"hello {0}, {1}\n"};
	//
	//using seq = xns::make_character_subsequence<sf, 6, 8>;
	//using seq2 = xns::make_character_subsequence<sf, 1, 3>;
	//
	//seq::print();
	////xns::static_tokenizer<seq> st;
	//
	//xns::basic_string_literal wsl{L"hello"};
	//
	//
	////constexpr char ar[1] = {'a'};
	//
	////constexpr xns::string_literal<char, 1> s{ar};
	//
	//constexpr xns::basic_string_literal s0{{'a', 'b', '\0'}};
	////constexpr xns::string_literal s0{"ab"};
	//
	////std::cout << "s0: " << s0.runtime_data() << std::endl;
	//std::cout << "s0: " << s0.size() << std::endl;
	//
	//if (s0 == L"ab") {
	//	std::cout << "equal" << std::endl;
	//}
	//else {
	//	std::cout << "not equal" << std::endl;
	//}
	//
	///*
	//xns::string_literal s2{s};
	//
	//std::cout << s2.runtime_data() << std::endl;
	//
	//
	//if (s.empty()) {
	//	std::cout << "empty: " << s.size() << std::endl;
	//}
	//else {
	//	std::cout << "not empty: " << s.size() << std::endl;
	//}
	//
	//xns::unix_path up{"/home/documents/notes.txt"};
	//
	//constexpr xns::string_literal l{U"🥸"};
	//xns::string_literal l2{"🥸"};
	//
	//
	//if (l == U"🥸") {
	//	std::cout << "equal" << std::endl;
	//}
	//else {
	//	std::cout << "not equal" << std::endl;
	//}
	//*/
	//
	//


	return 0;

}


#if defined(XNS_TEST_LITERAL_MAP)
int main(void) {
	return unit_tests_literal_map();
}
#endif



