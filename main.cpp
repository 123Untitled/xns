#include "tuple.hpp"
#include "vector.hpp"
#include "xfunc.hpp"

#include <array>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <stack>
#include <any>

#include "random.hpp"
#include "trie.hpp"

// const, left reference, right reference, volatile, const volatile

template <class T>
void func3(T&& arg) {

	if constexpr (Xf::is_lvalue_v<T>)
		std::cout << "left ref, ";
	else
		std::cout << "right ref, ";

	std::cout << "type: " << typeid(T).name() << ", ";
	std::cout << "value: " << arg << std::endl;
}


template <class... A>
void func2(A&&... args) {
	(func3(Xf::forward<A>(args)), ...);
}

template <class... A>
void func1(A&&... args) {
	func2(Xf::forward<A>(args)...);
}


int main(int ac, char** av) {

	const volatile int n = 10;
	float f = 10.0f;

	func1(n, f, 10, 10.0f);

	return EXIT_SUCCESS;




	Xf::Trie<std::string> trie;
	Xf::CString str = "hello";
	trie.insert(str, "world");
	trie.insert(str, "world2");

	Xf::AutoPointer<std::string> p = trie.find(Xf::CString{"hello"});

	std::cout << "check" << std::endl;
	if (p != nullptr) {
		std::cout << "found: " << *p << std::endl;
	}
	else {
		std::cout << "not found" << std::endl;
	}

    Xf::Vector<Xf::Tuple<int, float>> v;

    v.emplace_back(2, 2.2f);

	//char c = 'a';
	//int n = 10;
	//Xf::Tuple<char, int> tuple{'a', n};

	//UT::array_ut();
	//UT::tuple_ut();



	return EXIT_SUCCESS;

	for (auto i = 0; i < 10; ++i) {
		std::cout << Xf::Random::random(10) << std::endl;
	}

}





