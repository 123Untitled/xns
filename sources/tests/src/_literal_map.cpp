#include "containers/literal_map.hpp"
#include "containers/reference_wrapper.hpp"
#include <iostream>

class a {

	public:
		a(void) {
			std::cout << "a ctor" << std::endl;
		}
		a(const a&) {
			std::cout << "a copy ctor" << std::endl;
		}
		a(a&&) {
			std::cout << "a move ctor" << std::endl;
		}
		~a(void) {
			std::cout << "a dtor" << std::endl;
		}
		auto operator=(const a&) -> a& {
			std::cout << "a copy assign" << std::endl;
			return *this;
		}
		auto operator=(a&&) -> a& {
			std::cout << "a move assign" << std::endl;
			return *this;
		}

};

template <typename __type, xns::basic_string_literal... __literals>
auto print(const xns::literal_map<__type, __literals...>& __mp) -> void {

	__mp.for_each([](const __type& v) {
		std::cout << v << " ";
	});
	std::cout << std::endl;
}



auto unit_tests_literal_map(void) -> int {

	double d = 1.0;
	double e = 2.0;


	{
		xns::literal_map<xns::reference_wrapper<double>, "ref", "o"> m1{d, e};
		xns::get<"ref">(m1).get() = 3.0;

	double& ref = xns::get<"ref">(m1).get();
	ref = 1.0;
	}






	//std::cout << sizeof(xns::indexed_wrapper<0, a, true>) << std::endl;
	//std::cout << sizeof(xns::indexed_wrapper<0, a, false>) << std::endl;

	return 0;

	{
		xns::literal_map<double, "one", "two", "three"> m1{1.0, 2.0, 3.0};
		xns::literal_map<double, "one", "two", "three"> m2{};

		print(m1);
		print(m2);
		m2 = xns::move(m1);
		print(m1);
		print(m2);

		xns::literal_map<double, "one", "two", "three"> m3{m2};
		print(m3);
	}

	return 0;


	//bool bbb = (m2 == m) ? true : false;


	auto func = [](const a& v) {
		std::cout << "for_each: " << &v << std::endl;
	};

	//m.for_each(func);



	return 0;

	constexpr xns::literal_map<int, "a", "b"> m12 = { 1, 2 };


	xns::literal_map<int, "a", "b"> m1 = { 1, 2 };

	m1.size();

	std::cout << xns::get<"a">(m1) << std::endl;

	xns::get<"a">(m1) = xns::move(xns::get<"b">(m1));

	std::cout << xns::get<"a">(m1) << std::endl;


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



