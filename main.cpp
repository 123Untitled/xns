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


// curiously recurring template pattern (CRTP) learn

template <class T>
class _Base {
	public:
		_Base() = default;
		~_Base() = default;
};

class _Derived1 : public _Base<_Derived1> {
	public:
		_Derived1() = default;
		~_Derived1() = default;
};

class _Derived2 : public _Base<_Derived2> {
	public:
		_Derived2() = default;
		~_Derived2() = default;
};

class B {
	public:
		B() = default;
		virtual ~B() = default;
		virtual void echo() const = 0;
};

class D1 : public B {
	public:
		D1() = default;
		~D1() = default;
		void echo() const override {
			std::cout << "D1" << std::endl;
		}
};

class D2 : public B {
	public:
		D2() = default;
		~D2() = default;
		void echo() const override {
			std::cout << "D2" << std::endl;
		}
};

template <class T>
void invoke(const T& t) {
	Xf::AutoPointer<T> p = Xf::make_auto_pointer<T>(t);
	//(*p)();
}

Xf::AutoPointer<B> f() {
	return Xf::AutoPointer<D1>{};
}

int main(int ac, char** av) {


	using Proto = Xf::PolyMethod<Xf::AutoPointer<B>(void)>;

	Xf::PolyMethod<Xf::AutoPointer<B>(void)> pm{f};

	invoke<Proto>(pm);



	Xf::Trie<B> trie;

	trie.insert("hello", D1{});
	//Xf::Trie<Proto> trie3;

	//trie3.insert("hello", []() -> Xf::AutoPointer<B> {
	//	return Xf::AutoPointer<D1>{};
	//});






	Xf::AutoPointer<int> ap;
	Xf::WeakPointer<int> wp{ap};
	return EXIT_SUCCESS;




	Xf::Trie<std::string> trie2;
	Xf::CString str = "hello";
	trie2.insert(str, "world");
	trie2.insert(str, "world2");

	//Xf::AutoPointer<std::string> p = trie.find(Xf::CString{"hello"});


	/*
	std::cout << "check" << std::endl;
	if (p != nullptr) {
		std::cout << "found: " << *p << std::endl;
	}
	else {
		std::cout << "not found" << std::endl;
	}*/

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





